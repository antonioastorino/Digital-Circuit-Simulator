#include "DCSALU.hpp"
#include "DCSControlUnit5Bits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSInstructionSet.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSRam256x16.hpp"
#include "DCSRegister4Bits.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

void zeroFlagProgramTest() {
    DCSLog::printTestName("Zero flag program");
    uint64_t masterClockHP = 16;

    // the instruction is the MSHB and the data is the LSHB
    uint16_t program[16][2] = {{LDA, 15}, // instruction and operand 0
                               {LDB, 14}, // instruction and operand 1
                               {JEQ, 4},  // instruction and operand 2
                               {ADD, 15}, // instruction and operand 3
                               {HLT, 0},  // instruction and operand 4
                               {JMP, 0},  // instruction and operand 5
                               {0, 0},    {0, 0}, {0, 0}, {0, 0}, {0, 0},
                               {0, 0},    {0, 0}, {0, 4}, {0, 3}, {0, 3}};

    // RAM
    DCSEngine::initialize(masterClockHP);
    DCSRam16x8 ram("ram");
    DCSEngine::programMemory(&ram, program, false);

    DCSRam256x16 cuRam("cuRam");
    DCSEngine::programControlUnit(&cuRam, false);

    DCSEngine::useRamElements();

    // CU
    DCSControlUnit5Bits cu0("CU", &cuRam);

    // ALU
    DCSALU alu("alu");

    // Program counter
    DCSUpCounterWithLoadAndAsyncSR pc("pc", 4);

    // bus
    DCSComponentArray<DCSNode> bus("bus", 8);
    // // master clock
    DCSInput clk("clkSignal");
    clk.makeSquareWave(masterClockHP, true);
    DCSNot notClk("!CLK");
    DCSAnd clockSignal("andCLK");
    clk.connect(&clockSignal, 0, 0);
    notClk.connect(&clockSignal, 0, 1);

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

    DCSInput inGND("inGND");
    DCSInput inVCC("inVCC"); // RAM output enable (always 1)
    DCSInput inReset("inReset");

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
    alu.connect(&dispALU, {0, 7}, {0, 7});
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
    pc.connect(&trisPC, {0, 3}, {0, 3}); // Address from PC to trisPC
    for (uint16_t i = 4; i < 8; i++) {
        // signal meant to be constant at 0 and feed the MSb's of trisI. In this way, when trisI is
        // active and the LSb's are ouput to the bus, the MSb's are set to 0 instead of being the
        // same as the instruction.
        inGND.connect(&trisI, 0, i);  // zeros connected to the MSB of trisI
        inGND.connect(&trisPC, 0, i); // zeros connected to the MSB of trisPC
    }

    // connect registers A and B to ALU
    regA.connect(&alu, {0, 7}, {0, 7});
    regB.connect(&alu, {0, 7}, {8, 15});

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
    inGND.connect(&trisB, 0, 8, "BO"); // Connect output enable

    // connect control signals to memories
    // AR
    clockSignal.connect(&regA, 0, 8); // connect master clock to A
    inReset.connect(&regA, 0, 9, "");
    inGND.connect(&regA, 0, 10, "");
    // BR
    clockSignal.connect(&regB, 0, 8); // connect master clock to B
    inReset.connect(&regB, 0, 9, "");
    inGND.connect(&regB, 0, 10, "");
    // IR
    clockSignal.connect(&regI, 0, 8); // connect master clock to I
    inReset.connect(&regI, 0, 9, "");
    inGND.connect(&regI, 0, 10, "");
    // RAM
    clockSignal.connect(&ram, 0, 12); // connect master clock to RAM
    inGND.connect(&ram, 0, 13, "");   // Clear
    inGND.connect(&ram, 0, 14, "");   // Preset
    inVCC.connect(&ram, 0, 16);       // Output Enable
    // MAR
    clockSignal.connect(&mar, 0, 4); // connect master clock to MAR
    inReset.connect(&mar, 0, 5, "");
    inGND.connect(&mar, 0, 6, "");
    // PC
    clockSignal.connect(&pc, 0, 2); // connect master clock to PC
    inReset.connect(&pc, 0, 3, "");
    inGND.connect(&pc, 0, 4, "");
    // Output register
    clockSignal.connect(&regOut, 0, 8); // connect master clock to OUT
    inReset.connect(&regOut, 0, 9, "");
    inGND.connect(&regOut, 0, 10, "");

    clockSignal.connect(&cu0, 0, 0);
    inReset.connect(&cu0, 0, 1);
    regI.connect(&cu0, {4, 7}, {2, 5}); // connect Instruction Register MSHB to Control Unit
    alu.connect(&cu0, 9, 6, "Z");    // Flag in
    cu0.connect(&pc, 1, 1, "J");        // Jump
    cu0.connect(&trisPC, 2, 8, "CO");   // Connect output enable
    cu0.connect(&pc, 3, 0, "CE");       // Count enable
    cu0.connect(&regOut, 4, 11, "OI");
    cu0.connect(&regB, 5, 11, "BI");
    cu0.connect(&alu, 6, 16, "SU");
    cu0.connect(&trisALU, 7, 8, "EO"); // Connect output enable
    cu0.connect(&trisA, 8, 8, "AO");   // Connect output enable
    cu0.connect(&regA, 9, 11, "AI");
    cu0.connect(&regI, 10, 11, "II");
    cu0.connect(&trisI, 11, 8, "IO");   // Connect output enable
    cu0.connect(&trisRAM, 12, 8, "RO"); // Connect output enable
    cu0.connect(&ram, 13, 15, "RI");
    cu0.connect(&mar, 14, 7, "MI");
    cu0.connect(&notClk, 15, 0, "HLT"); // the negated HLT signal will stop the clock

    // constant signals
    inVCC.makeSignal("01", true); // The RAM is always enable to always talk to the IR. A 3-state
                                  // buffer is placed between RAM and bus
    inGND.makeSignal(0);
    std::string dn("00");           // do nothing (while resetting the registers)
    inReset.makeSignal("10", true); // initialize by resetting the register

    DCSEngine::run(80 * masterClockHP, true); //*/
}
