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

void Computer() {
    DCSLog::printTestName("Computer");
    uint16_t masterClockHP = 13;
    DCSEngine::initialize(masterClockHP);

    // RAM
    DCSRam16x8 ram("ram");
    
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
    DCSRegister8Bits regA("AR"); // A register
    DCSRegister8Bits regB("BR"); // B register
    DCSRegister8Bits regI("IR"); // Instruction register
    DCSRegister4Bits mar("mar"); // Memory address register

    // displays
    DCSDisplayNBits dispA("outA", 8);      // A register output display
    DCSDisplayNBits dispB("outB", 8);      // B register output display
    DCSDisplayNBits dispI0("instr", 4);    // I register output display
    DCSDisplayNBits dispI1("operand", 4);  // I register output display
    DCSDisplayNBits dispALU("alu", 8);     // ALU output display
    DCSDisplayNBits dispBus("dispBus", 8); // bus display
    DCSDisplayNBits dispMAR("dispMAR", 4); // MAR display
    DCSDisplayNBits dispRAM("dispRAM", 8); // RAM display

    // signal meant to be constant at 0 and feed the MSb's of trisI. In this way, when trisI is
    // active and the LSb's are ouput to the bus, the MSb's are set to 0 instead of being the same
    // as the instruction.
    DCSComponentArray<DCSInput> zero4("zero4", 4);

    // // Data in signals (to be replaced with the bus)
    DCSComponentArray<DCSInput> inA("inA", 8);

    // Control signals (to be replaced with CU signals)
    DCSInput inResA("inResA");
    DCSInput inResB("inResB");
    DCSInput inResI("inResI");
    DCSInput inResRAM("inResRAM");
    DCSInput inResMAR("inResMAR");
    DCSInput inResPC("inResPC");
    DCSInput inPresA("inPresA");
    DCSInput inPresB("inPresB");
    DCSInput inPresI("inPresI");
    DCSInput inPresRAM("inPresRAM");
    DCSInput inPresMAR("inPresMAR");
    DCSInput inPresPC("inPresPC");
    DCSInput inAI("inAI");
    DCSInput inBI("inBI");
    DCSInput inII("inII");
    DCSInput inRI("inRI");
    DCSInput inMI("inMI");
    DCSInput inJ("inJ");
    DCSInput inAO("inAO");   // A register out
    DCSInput inBO("inBO");   // B register out
    DCSInput inIO("inIO");   // Instruction register out
    DCSInput inOeRAM("oeR"); // RAM output enable (always 1)
    DCSInput inRO("inRO");   // RAM out
    DCSInput inSU("inSU");   // add/subtract ALU signal
    DCSInput inEO("inEO");   // ALU out
    DCSInput inCE("inCE");   // count enable

    // 3-state buffers
    DCSTriStateBuffer8Bits trisA("trisA");
    DCSTriStateBuffer8Bits trisB("trisB");
    DCSTriStateBuffer8Bits trisI("trisI");
    DCSTriStateBuffer8Bits trisALU("trisALU");
    DCSTriStateBuffer8Bits trisRAM("trisRAM");

    // connect to registers' and RAM's data input
    inA.connect(&regA, {0, 7}, {0, 7}); // Data in
    bus.connect(&regB, {0, 7}, {0, 7}); // Data input from the bus
    bus.connect(&ram, {0, 7}, {0, 7});  // Data input from the bus
    ram.connect(&regI, {0, 7}, {0, 7}); // Data from RAM to I register
    pc.connect(&mar, {0, 3}, {0, 3});   // Address from PC to MAR
    bus.connect(&pc, {0, 3}, {5, 8});   // PC Address from bus

    // connect component data out to displays
    regA.connect(&dispA);
    regB.connect(&dispB);
    regI.connect(&dispI0, {4, 7}, {0, 3}); // display operand
    regI.connect(&dispI1, {0, 3}, {0, 3}); // display instruction
    alu.connect(&dispALU);
    mar.connect(&dispMAR);
    ram.connect(&dispRAM);
    bus.connect(&dispBus);

    // connect component data out to tri-state buffer
    regA.connect(&trisA, {0, 7}, {0, 7});  // Tri-state buffering the data
    regB.connect(&trisB, {0, 7}, {0, 7});  // Tri-state buffering the data
    regI.connect(&trisI, {0, 3}, {0, 3});  // Tri-state buffering the data
    alu.connect(&trisALU, {0, 7}, {0, 7});
    ram.connect(&trisRAM, {0, 7}, {0, 7});
    zero4.connect(&trisI, {0, 3}, {4, 7}); // zeros connected to the MSB of trisI

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
    trisALU.connect(&bus);               // Operand output to the bus
    trisRAM.connect(&bus);               // Operand output to the bus

    // connect tri-state buffer control signals to buffers
    inAO.connect(&trisA, 0, 8, "AO");   // Connect output enable
    inBO.connect(&trisB, 0, 8, "BO");   // Connect output enable
    inIO.connect(&trisI, 0, 8, "IO");   // Connect output enable
    inEO.connect(&trisALU, 0, 8, "EO"); // Connect output enable
    inRO.connect(&trisRAM, 0, 8, "RO"); // Connect output enable

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
    masterClock.connect(&mar, 0, 4);  // connect master clock to MAR
    inResMAR.connect(&mar, 0, 5, "");
    inPresMAR.connect(&mar, 0, 6, "");
    inMI.connect(&mar, 0, 7, "MI");
    // PC
    masterClock.connect(&pc, 0, 2);   // connect master clock to PC
    inResPC.connect(&pc, 0, 3, "");
    inPresPC.connect(&pc, 0, 4, "");
    inJ.connect(&pc, 0, 1); // Jump
    inCE.connect(&pc, 0, 0); // Count enable

    // constant signals
    inOeRAM.makeSignal(1); // The RAM is always enable to always talk to the IR. A 3-state buffer is
                           // placed between RAM and bus
    zero4[0]->makeSignal(0);
    zero4[1]->makeSignal(0);
    zero4[2]->makeSignal(0);
    zero4[3]->makeSignal(0);

    // test signals
    inAO.makeSignal("11000", true);
    inBO.makeSignal("00100", true);
    inIO.makeSignal("000110", true);
    inEO.makeSignal("000001", true);
    inSU.makeSignal("0001110", true);
    inAI.makeSignal("1000000", true);
    inBI.makeSignal("0100001", true);

    inA[0]->makeSignal(0);
    inA[1]->makeSignal(1);
    inA[2]->makeSignal(0);
    inA[3]->makeSignal(0);
    inA[4]->makeSignal(0);
    inA[5]->makeSignal(0);
    inA[6]->makeSignal(0);
    inA[7]->makeSignal(0);

    DCSEngine::run(20 * masterClockHP, true); //*/
}
