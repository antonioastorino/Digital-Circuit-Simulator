#include "DCSALU.hpp"
#include "DCSAnd.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSRegister4Bits.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

// based on https://www.youtube.com/watch?v=dXdoim96v5A&list=PLowKtXNTBypGqImE405J2565dvjafglHU&index=36
void Computer() {
    DCSLog::printTestName("Computer");
    uint16_t masterClockHP = 20;

    // Instruction set
    uint16_t LDA = 0b0001; // Load in reg A
    uint16_t STA = 0b0000; // Store A in RAM
    uint16_t LDI = 0b0101; // Load immediate to A reg
    uint16_t ADD = 0b0010; // Add value from location in RAM to reg A and store in B
    uint16_t SUB = 0b0011; // Subtract value from location in RAM to reg A and store in B
    uint16_t JMP = 0b0110; // Jump
    uint16_t OUT = 0b1110; // Output
    uint16_t HLT = 0b1111; // Halt

    // the instruction is the MSHB and the data is the LSHB
    uint16_t program[16][2] = {
        {LDA, 14}, // store LDA and 14 at location 0
        {ADD, 15}, // store ADD and 15 at location 1
        {OUT, 0},  // store OUT and 0 at location 2
        {0, 0},    // store 0 at location 3
        {0, 0},    // store 0 at location 4
        {0, 0},    // store 0 at location 5
        {0, 0},    // store 0 at location 6
        {0, 0},    // store 0 at location 7
        {0, 0},    // store 0 at location 8
        {0, 0},    // store 0 at location 9
        {0, 0},    // store 0 at location 10
        {0, 0},    // store 0 at location 11
        {0, 0},    // store 0 at location 12
        {0, 0},    // store 0 at location 13
        {0, 28},   // store 28 at location 14
        {0, 14}    // store 14 at location 15
    };

    // RAM
    DCSEngine::initialize(masterClockHP);
    DCSRam16x8 ram("ram");
    DCSEngine::programMemory(&ram, program, false);

    // ALU
    DCSALU alu("alu");

    // Program counter
    DCSUpCounterWithLoadAndAsyncSR pc("pc", 4);

    // bus
    DCSComponentArray<DCSNode> bus("bus", 8);

    // // master clock
    DCSInput clockSignal("clkSignal");
    DCSNode masterClock("clkNode");
    clockSignal.connect(&masterClock, {"MCLK"});
    clockSignal.makeSquareWave(masterClockHP, true);

    // registers
    DCSRegister8Bits regA("regA");     // A register
    DCSRegister8Bits regB("regB");     // B register
    DCSRegister8Bits regI("regI");     // Instruction register
    DCSRegister8Bits regOut("regOut"); // Output register
    DCSRegister4Bits mar("mar");       // Memory address register

    // displays
    DCSDisplayNBits dispA("outA", 8);      // A register output display
    DCSDisplayNBits dispB("outB", 8);      // B register output display
    DCSDisplayNBits dispI0("instr", 4);    // I register output display
    DCSDisplayNBits dispI1("operand", 4);  // I register output display
    DCSDisplayNBits dispALU("alu", 8);     // ALU output display
    DCSDisplayNBits dispOut("dispOut", 8); // Out display
    DCSDisplayNBits dispMAR("dispMAR", 4); // MAR display
    DCSDisplayNBits dispRAM("dispRAM", 8); // RAM display
    DCSDisplayNBits dispPC("dispPC", 4);   // PC display

    // signal meant to be constant at 0 and feed the MSb's of trisI. In this way, when trisI is
    // active and the LSb's are ouput to the bus, the MSb's are set to 0 instead of being the same
    // as the instruction.
    DCSComponentArray<DCSInput> zero4("zero4", 4);

    // Control signals (to be replaced with CU signals)
    DCSInput inResA("inResA");
    DCSInput inResB("inResB");
    DCSInput inResI("inResI");
    DCSInput inResRAM("inResRAM");
    DCSInput inResMAR("inResMAR");
    DCSInput inResPC("inResPC");
    DCSInput inResO("inResO");
    DCSInput inPresA("inPresA");
    DCSInput inPresB("inPresB");
    DCSInput inPresI("inPresI");
    DCSInput inPresRAM("inPresRAM");
    DCSInput inPresMAR("inPresMAR");
    DCSInput inPresPC("inPresPC");
    DCSInput inPresO("inPresO");
    DCSInput inAI("inAI");
    DCSInput inBI("inBI");
    DCSInput inII("inII");
    DCSInput inRI("inRI");
    DCSInput inMI("inMI");
    DCSInput inJ("inJ");
    DCSInput inOI("inOI");
    DCSInput inAO("inAO");   // A register out to the bus
    DCSInput inBO("inBO");   // B register out to the bus
    DCSInput inIO("inIO");   // Instruction register out to the bus
    DCSInput inOeRAM("oeR"); // RAM output enable (always 1)
    DCSInput inRO("inRO");   // RAM out to the bus
    DCSInput inSU("inSU");   // add/subtract ALU signal
    DCSInput inEO("inEO");   // ALU out to the bus
    DCSInput inCO("inCO");   // PC out to the bus
    DCSInput inCE("inCE");   // count enable

    // 3-state buffers
    DCSTriStateBuffer8Bits trisA("trisA");
    DCSTriStateBuffer8Bits trisB("trisB");
    DCSTriStateBuffer8Bits trisI("trisI");
    DCSTriStateBuffer8Bits trisALU("trisALU");
    DCSTriStateBuffer8Bits trisRAM("trisRAM");
    DCSTriStateBuffer8Bits trisPC("trisPC");

    // connect to registers' and RAM's data input
    bus.connect(&regA, {0, 7}, {0, 7});   // Data input from the bus
    bus.connect(&regB, {0, 7}, {0, 7});   // Data input from the bus
    bus.connect(&ram, {0, 7}, {0, 7});    // Data input from the bus
    ram.connect(&regI, {0, 7}, {0, 7});   // Data from RAM to I register
    bus.connect(&pc, {0, 3}, {5, 8});     // PC Address from bus
    bus.connect(&mar, {0, 3}, {0, 3});    // PC Address from bus
    bus.connect(&regOut, {0, 7}, {0, 7}); // bus to OUT register

    // connect component data out to displays
    regA.connect(&dispA);
    regB.connect(&dispB);
    regI.connect(&dispI0, {4, 7}, {0, 3}); // display operand
    regI.connect(&dispI1, {0, 3}, {0, 3}); // display instruction
    alu.connect(&dispALU);
    mar.connect(&dispMAR);
    ram.connect(&dispRAM);
    regOut.connect(&dispOut);
    pc.connect(&dispPC, {0, 3}, {0, 3});

    // connect component data out to tri-state buffer
    regA.connect(&trisA, {0, 7}, {0, 7}); // Tri-state buffering the data
    regB.connect(&trisB, {0, 7}, {0, 7}); // Tri-state buffering the data
    regI.connect(&trisI, {0, 3}, {0, 3}); // Tri-state buffering the data
    alu.connect(&trisALU, {0, 7}, {0, 7});
    ram.connect(&trisRAM, {0, 7}, {0, 7});
    pc.connect(&trisPC, {0, 3}, {0, 3});    // Address from PC to trisPC
    zero4.connect(&trisI, {0, 3}, {4, 7});  // zeros connected to the MSB of trisI
    zero4.connect(&trisPC, {0, 3}, {4, 7}); // zeros connected to the MSB of trisPC

    // connect registers A and B to ALU
    regA.connect(&alu, {0, 7}, {0, 7});
    regB.connect(&alu, {0, 7}, {8, 15});

    // connect alu control signals to ALU
    inSU.connect(&alu, 0, 16, "SU");

    // connect MAR to RAM
    mar.connect(&ram, {0, 3}, {8, 11});

    // connect tri-state buffers to bus
    trisA.connect(&bus);
    trisB.connect(&bus);                 // Data output to the bus
    trisI.connect(&bus, {0, 3}, {0, 3}); // Operand output to the bus
    trisALU.connect(&bus);               // ALU output to the bus
    trisRAM.connect(&bus);               // RAM output to the bus
    trisPC.connect(&bus);                // PC output to the bus

    // connect tri-state buffer control signals to buffers
    inAO.connect(&trisA, 0, 8, "AO");   // Connect output enable
    inBO.connect(&trisB, 0, 8, "BO");   // Connect output enable
    inIO.connect(&trisI, 0, 8, "IO");   // Connect output enable
    inEO.connect(&trisALU, 0, 8, "EO"); // Connect output enable
    inRO.connect(&trisRAM, 0, 8, "RO"); // Connect output enable
    inCO.connect(&trisPC, 0, 8, "CO");  // Connect output enable

    // connect control signals to memories
    // AR
    masterClock.connect(&regA, 0, 8); // connect master clock to A
    inResA.connect(&regA, 0, 9, "");
    inPresA.connect(&regA, 0, 10, "");
    inAI.connect(&regA, 0, 11, "AI");
    // BR
    masterClock.connect(&regB, 0, 8); // connect master clock to B
    inResB.connect(&regB, 0, 9, "");
    inPresB.connect(&regB, 0, 10, "");
    inBI.connect(&regB, 0, 11, "BI");
    // IR
    masterClock.connect(&regI, 0, 8); // connect master clock to I
    inResI.connect(&regI, 0, 9, "");
    inPresI.connect(&regI, 0, 10, "");
    inII.connect(&regI, 0, 11, "II");
    // RAM
    masterClock.connect(&ram, 0, 12); // connect master clock to RAM
    inResRAM.connect(&ram, 0, 13, "");
    inPresRAM.connect(&ram, 0, 14, "");
    inRI.connect(&ram, 0, 15, "RI");
    inOeRAM.connect(&ram, 0, 16);
    // MAR
    masterClock.connect(&mar, 0, 4); // connect master clock to MAR
    inResMAR.connect(&mar, 0, 5, "");
    inPresMAR.connect(&mar, 0, 6, "");
    inMI.connect(&mar, 0, 7, "MI");
    // PC
    masterClock.connect(&pc, 0, 2); // connect master clock to PC
    inResPC.connect(&pc, 0, 3, "");
    inPresPC.connect(&pc, 0, 4, "");
    inJ.connect(&pc, 0, 1);  // Jump
    inCE.connect(&pc, 0, 0); // Count enable
    // Output register
    masterClock.connect(&regOut, 0, 8); // connect master clock to OUT
    inResO.connect(&regOut, 0, 9, "");
    inPresO.connect(&regOut, 0, 10, "");
    inOI.connect(&regOut, 0, 11, "OI");

    // constant signals
    inOeRAM.makeSignal(1); // The RAM is always enable to always talk to the IR. A 3-state buffer is
                           // placed between RAM and bus
    zero4[0]->makeSignal(0);
    zero4[1]->makeSignal(0);
    zero4[2]->makeSignal(0);
    zero4[3]->makeSignal(0);

    // test signals
    std::string dn("00");            // do nothing (while resetting the registers)
    inResA.makeSignal("10", true);   // initialize by resetting the register
    inResB.makeSignal("10", true);   // initialize by resetting the register
    inResI.makeSignal("10", true);   // initialize by resetting the register
    inResMAR.makeSignal("10", true); // initialize by resetting the register
    inResPC.makeSignal("10", true);  // initialize by resetting the register
    inResO.makeSignal("10", true);   // initialize by resetting the register

    // manual execution of microcode
    inSU.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "000" + "00" + "000" + "00" + "000", true);
    inAI.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "010" + "00" + "001" + "00" + "000", true);
    inBI.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "000" + "00" + "010" + "00" + "000", true);
    inII.makeSignal(dn + /*fetch*/ "01" + /*dec*/ "000" + "01" + "000" + "01" + "000", true);
    inRO.makeSignal(dn + /*fetch*/ "01" + /*dec*/ "010" + "01" + "010" + "01" + "000", true);
    inMI.makeSignal(dn + /*fetch*/ "10" + /*dec*/ "100" + "10" + "100" + "10" + "000", true);
    inAO.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "000" + "00" + "000" + "00" + "100", true);
    inBO.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "000" + "00" + "000" + "00" + "000", true);
    inIO.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "100" + "00" + "100" + "00" + "000", true);
    inEO.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "000" + "00" + "001" + "00" + "000", true);
    inCO.makeSignal(dn + /*fetch*/ "10" + /*dec*/ "000" + "10" + "000" + "10" + "000", true);
    inCE.makeSignal(dn + /*fetch*/ "01" + /*dec*/ "000" + "01" + "010" + "01" + "000", true);
    inOI.makeSignal(dn + /*fetch*/ "00" + /*dec*/ "000" + "00" + "000" + "00" + "100", true);

    DCSEngine::run(40 * masterClockHP, true); //*/
}
