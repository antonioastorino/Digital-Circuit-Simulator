#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam256x16.hpp"

void controlUnitTest() {
	DCSLog::printTestName("Control Unit");
    uint32_t hp = 12;
    DCSEngine::initialize(hp);
    
	DCSRam256x16 cu0("cu");

	DCSEngine::programControlUnit(&cu0);

    DCSComponentArray<DCSInput> inData("inData", 16);
    DCSComponentArray<DCSInput> inAddress("inAddress", 8);
    DCSComponentArray<DCSInput> inCtrl("inCtrl", 5);

    DCSDisplayNBits dispAddr("addr", 8);
    DCSDisplayNBits dispOut("out", 16);

    inData.connect(&cu0, {0, 15}, {0, 15});
    inAddress.connect(&cu0, {0, 7}, {16, 23});
    inAddress.connect(&dispAddr);
    inCtrl.connect(&cu0, {0, 4}, {24, 28}, {"clk", "R", "S", "LD", "OE"});

    cu0.connect(&dispOut);

    for (uint16_t i = 0; i < 7; i++) {
        inAddress[i]->makeSquareWave(hp << (i+1), 0);
    }
    inCtrl[0]->makeSquareWave(hp);
    inCtrl[3]->makeSignal(transitions({16, 1}), true, true);
    inCtrl[4]->makeSignal(1);

    DCSEngine::run(20 * hp + 3, true);
}
