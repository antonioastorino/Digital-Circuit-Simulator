#include "test-Ram256x16.hpp"

void ram256x16Test() {
    DCSLog::printTestName("Ram 256 words, 16 bits");
    uint32_t hp = 12;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inData("inData", 16);
    DCSComponentArray<DCSInput> inAddress("inAddress", 8);
    DCSComponentArray<DCSInput> inCtrl("inCtrl", 5);

    DCSRam256x16 ram0("ram");
    DCSDisplayNBits dispIn("in", 16);
    DCSDisplayNBits dispAddr("addr", 8);
    DCSDisplayNBits dispOut("out", 16);

    inData.connect(&ram0, {0, 15}, {0, 15});
    inData.connect(&dispIn, {0, 15}, {0, 15});
    inAddress.connect(&ram0, {0, 7}, {16, 23});
    inAddress.connect(&dispAddr);
    inCtrl.connect(&ram0, {0, 4}, {24, 28}, {"clk", "R", "S", "LD", "OE"});

    ram0.connect(&dispOut);

    for (uint16_t i = 0; i < 16; i++) {
        inData[i]->makeSquareWave(hp << ((i % 4) + 1), 0);
    }
    for (uint16_t i = 0; i < 7; i++) {
        inAddress[i]->makeSquareWave(hp << ((i % 4) + 1), 0);
    }
    inCtrl[0]->makeSquareWave(hp);
    inCtrl[3]->makeSignal(transitions({16, 1}), true, true);
    inCtrl[4]->makeSignal(1);

    DCSEngine::run(20 * hp + 3, true);
}
