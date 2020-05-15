#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSInstructionSet.hpp"

void memoryProgrammerTest() {
    DCSLog::printTestName("Memory programmer");

    // the instruction is the MSHB and the data is the LSHB
    uint16_t program[16][2] = {{LDI, 3},  // instruction and operand 0
                               {STA, 15}, // instruction and operand 1
                               {LDI, 0},  // instruction and operand 2
                               {ADD, 15}, // instruction and operand 3
                               {OUT, 0},  // instruction and operand 4
                               {JMP, 3},  // instruction and operand 5
                               {0, 0},    {0, 0}, {0, 0}, {0, 0}, {0, 0},
                               {0, 0},    {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    uint16_t hcp = 15;
    DCSEngine::initialize(hcp);

    /*
    IMPORTANT: initialize() and DCSEngine::programMemory()
    */
    DCSRam16x8 ram("r");

    DCSEngine::programMemory(&ram, program);
    DCSEngine::useRamElements();

    DCSComponentArray<DCSInput> inArray0("In", ram.getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray0("Out", 5);

    DCSDisplayNBits dispAddr("ADDR", 4);
    DCSDisplayNBits dispData("DATA", 8);
    DCSDisplayNBits dispOut("OUT", 8);

    inArray0.connect(&ram);
    inArray0.connect(&dispData, {0, 7}, {0, 7});
    inArray0.connect(&dispAddr, {8, 11}, {0, 3});
    inArray0.connect(&outArray0, {12, 16}, {0, 4}, {"CLK", "R", "S", "WR", "OE"});
    ram.connect(&dispOut);

    inArray0[5]->makeSignal(std::string("0000011100"));
    inArray0[7]->makeSignal(std::string("0000011100"));
    inArray0[8]->makeSquareWave(1 * hcp);
    inArray0[9]->makeSquareWave(2 * hcp);
    inArray0[10]->makeSquareWave(4 * hcp);
    inArray0[11]->makeSquareWave(8 * hcp);
    inArray0[12]->makeSignal(1); // CLK
    inArray0[13]->makeSignal(0); // Clear
    inArray0[14]->makeSignal(0); // Preset
    inArray0[15]->makeSignal(0); // Write
    inArray0[16]->makeSignal(1); // Enable
    DCSEngine::run(16 * hcp, true);
}
