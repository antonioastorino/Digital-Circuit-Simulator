#include "test-Ram.hpp"

void ramTest() {
    DCSLog::printTestName("RAM");

    uint16_t hcp = 10; // half clock period
    DCSEngine::initialize(hcp);
    DCSRam16x8 ram0("Ram0");

    DCSComponentArray<DCSInput> inArray0("In", ram0.getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray0("Out", 5);

    DCSDisplayNBits dispAddr("ADDR", 4);
    DCSDisplayNBits dispData("DATA", 8);
    // DCSDisplayNBits dispCtrl("CTRL", 5);
    DCSDisplayNBits dispOut("OUT", 8);

    inArray0.connect(&ram0);
    inArray0.connect(&dispAddr, {8, 11}, {0, 3});
    inArray0.connect(&dispData, {0, 7}, {0, 7});
    inArray0.connect(&outArray0, {12, 16}, {0, 4}, {"CLK", "R", "S", "WR", "OE"});
    ram0.connect(&dispOut);

    inArray0[0]->makeSignal(std::string("0000011100"));   // Data in 0
    inArray0[7]->makeSignal(std::string("0000011100"));   // Data in 1
    inArray0[8]->makeSignal({2, 1, 1}, 0, true);          // Address 0
    inArray0[16]->makeSignal(1);                          // Enable
    inArray0[12]->makeSignal(std::string("11111111001")); // Clock
    inArray0[13]->makeSignal(std::string("1111000000"));  // Clear
    inArray0[14]->makeSignal({5, 1, 1}, 0, true);         // Preset
    inArray0[15]->makeSignal(1);                          // Write

    DCSEngine::run(15 * hcp, false);
}