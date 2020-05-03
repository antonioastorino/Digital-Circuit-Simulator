#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

void firstProgramTest() {
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
    uint16_t program[16][2] = {{LDI, 3}, {STA, 15}, {LDI, 0}, {ADD, 15}, {OUT, 0}, {JMP, 3},
                               {0, 0},   {0, 0},    {0, 0},   {0, 0},    {0, 0},   {0, 0},
                               {0, 0},   {0, 0},    {0, 0},   {0, 0}};

    DCSLog::printTestName("First program");
    uint16_t hcp = 10;
    DCSEngine::initialize(hcp);

    DCSRam16x8* ram = new DCSRam16x8("r");
    DCSEngine::programMemory(ram, program);

    DCSComponentArray<DCSInput> inArray0("In", ram->getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray0("Out", 5);

    DCSDisplayNBits dispAddr("ADDR", 4);
    DCSDisplayNBits dispData("DATA", 8);
    DCSDisplayNBits dispOut("OUT", 8);

    inArray0.connect(ram);
    inArray0.connect(&dispAddr, {13, 16}, {0, 3});
    inArray0.connect(&dispData, {5, 12}, {0, 7});
    inArray0.connect(&outArray0, {0, 4}, {0, 4}, {"OE", "CLK", "R", "S", "WR"});
    ram->connect(&dispOut);

    inArray0[0]->makeSignal(1); // Enable
    inArray0[1]->makeSignal(1); // CLK
    inArray0[2]->makeSignal(0); // Clear
    inArray0[3]->makeSignal(0); // Preset
    inArray0[4]->makeSignal(0); // Write
    inArray0[5]->makeSignal(std::string("0000011100"));
    inArray0[7]->makeSignal(std::string("0000011100"));
    inArray0[15]->makeSignal({2, 1, 1}, 0, true);
    // READ MEMORY
    DCSEngine::run(15 * hcp, true);
}
