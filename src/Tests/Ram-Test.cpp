#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSRam16x8.hpp"
#include "DCSOutput.hpp"

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
    inArray0.connect(&dispAddr, {13, 16}, {0, 3});
    inArray0.connect(&dispData, {5, 12}, {0, 7});
    inArray0.connect(&outArray0, {0, 4}, {0, 4}, {"OE", "CLK", "R", "S", "WR"});
    ram0.connect(&dispOut);

    inArray0[0]->makeSignal(1); // Enable
    inArray0[1]->makeSignal(std::string("1111111001"));
    inArray0[2]->makeSignal(std::string("1111000000")); // Clear
    inArray0[3]->makeSignal({5, 1, 1}, 0, true);       // Preset
    inArray0[4]->makeSignal(1); // Write
    inArray0[5]->makeSignal(std::string("0000011100"));
    inArray0[7]->makeSignal(std::string("0000011100"));
    inArray0[15]->makeSignal({2, 1, 1}, 0, true);

    DCSEngine::run(15 * hcp, false);
}