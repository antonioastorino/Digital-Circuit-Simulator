#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSTimer.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

void firstProgramTest() {
    DCSLog::printTestName("First program");
    PROFILE_WITH_CUSTOM_NAME("App");
    // Instruction set
    uint16_t LDA = 0b0000; // Load in reg A
    uint16_t STA = 0b0000; // Store A in RAM
    uint16_t LDI = 0b0101; // Load immediate to A reg
    uint16_t ADD = 0b0010; // Add value from location in RAM to reg A and store in B
    uint16_t SUB = 0b0011; // Subtract value from location in RAM to reg A and store in B
    uint16_t JMP = 0b0110; // Jump
    uint16_t OUT = 0b1110; // Output
    uint16_t HLT = 0b1111; // Halt

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
    {
        PROFILE_WITH_CUSTOM_NAME("Init engine");
        DCSEngine::initialize(hcp);
    }

    /*
    IMPORTANT: initialize() and DCSEngine::programMemory()
    */
    DCSRam16x8 ram("r");

    {
        PROFILE_WITH_CUSTOM_NAME("Load memory");
        DCSEngine::programMemory(&ram, program);
    }

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
    {
        PROFILE_WITH_CUSTOM_NAME("Run loop");
        DCSEngine::run(16 * hcp, true);
    }
}
