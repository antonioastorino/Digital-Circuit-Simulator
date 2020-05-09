#include "DCSAnd.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSTriStateBuffer8Bits.hpp"

void Computer() {
    DCSLog::printTestName("Computer");
    {
        uint16_t masterClockHP = 10;
        DCSEngine::initialize(masterClockHP);

        // bus
        DCSComponentArray<DCSNode> bus("bus", 8);
        DCSDisplayNBits dispBus("dispBus", 8);
        bus.connect(&dispBus);

        // // master clock
        DCSInput clock("clkSignal");
        DCSNode nodeClock("clkNode");
        clock.connect(&nodeClock, {"MCLK"});
        clock.makeSquareWave(masterClockHP, true);

        // // register A
        // // Data in signals (to be replaced with the bus)
        DCSComponentArray<DCSInput> inA("inA", 8);
        // // Control signals (to be replaced with CU signals)

        DCSRegister8Bits regA("AR");      // A register
        DCSRegister8Bits regB("BR");      // B register
        DCSRegister8Bits regI("IR");      // Instruction register
        DCSDisplayNBits dispA("outA", 8); // A register output display
        DCSDisplayNBits dispB("outB", 8); // B register output display
        DCSDisplayNBits dispI0("instr", 4); // I register output display
        DCSDisplayNBits dispI1("operand", 4); // I register output display

        // Control signals (to be replaced with CU signals)
        DCSInput presA("presA");
        DCSInput presB("presB");
        DCSInput presI("presI");
        DCSInput resA("resA");
        DCSInput resB("resB");
        DCSInput resI("resI");
        DCSInput loadA("loadA");
        DCSInput loadB("loadB");
        DCSInput loadI("loadI");

        DCSInput oeA("oeA");
        DCSInput oeB("oeB");
        DCSInput oeI("oeI");
        DCSTriStateBuffer8Bits trisA("trisA");
        DCSTriStateBuffer8Bits trisB("trisB");
        DCSTriStateBuffer8Bits trisI("trisI");

        // connect data in to registers
        inA.connect(&regA, {0, 7}, {0, 7}); // Data in
        bus.connect(&regB, {0, 7}, {0, 7}); // Data input from the bus
        bus.connect(&regI, {0, 7}, {0, 7}); // Data input from the bus
        
        // connect register data out to display
        regA.connect(&dispA);
        regB.connect(&dispB);
        regI.connect(&dispI0, {4, 7}, {0,3});
        regI.connect(&dispI1, {0, 3}, {0, 3});
        
        // connect register data out to tri-state buffer
        regA.connect(&trisA, {0,7}, {0, 7}); // Tri-state buffering the data
        regB.connect(&trisB, {0,7}, {0, 7}); // Tri-state buffering the data
        regI.connect(&trisI, {0,7}, {0, 7}); // Tri-state buffering the data

        // connect tri-state buffer control signals to buffers
        oeA.connect(&trisA, 0, 8, "OEA"); // Connect output enable
        oeB.connect(&trisB, 0, 8, "OEB"); // Connect output enable
        oeI.connect(&trisI, 0, 8, "OEI"); // Connect output enable
        
        // connect tri-state buffers to bus
        trisA.connect(&bus);
        trisB.connect(&bus); // Data output to the bus
        trisI.connect(&bus, {4, 7}, {0,3}); // Operand output to the bus

        // connect register control signals to registers
        presA.connect(&regA, 0, 9, "");
        presB.connect(&regB, 0, 9, "");
        presI.connect(&regI, 0, 9, "");
        resA.connect(&regA, 0, 10, "");
        resB.connect(&regB, 0, 10, "");
        resI.connect(&regI, 0, 10, "");
        loadA.connect(&regA, 0, 11, "loadA");
        loadB.connect(&regB, 0, 11, "loadB");
        loadI.connect(&regI, 0, 11, "loadI");
        nodeClock.connect(&regA, 0, 8); // connect master clock to A
        nodeClock.connect(&regB, 0, 8); // connect master clock to B
        nodeClock.connect(&regI, 0, 8); // connect master clock to B

        // generate test signals
        oeA.makeSignal("11000", true);
        oeB.makeSignal("00100", true);
        oeI.makeSignal("00011", true);
        inA[0]->makeSignal(0);
        inA[1]->makeSignal(1);
        inA[2]->makeSignal(0);
        inA[3]->makeSignal(1);
        inA[4]->makeSignal(0);
        inA[5]->makeSignal(1);
        inA[6]->makeSignal(0);
        inA[7]->makeSignal(1);

        loadA.makeSignal("100", true);
        loadB.makeSignal("010", true);

        DCSEngine::run(8 * masterClockHP, false);
    }
}
