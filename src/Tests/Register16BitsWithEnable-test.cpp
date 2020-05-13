#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister16BitsWithEnable.hpp"

void register16BitsWithEnableTest() {
    DCSLog::printTestName("16-bit register with enable");
    DCSEngine::initialize(1);

    DCSRegister16BitsWithEnable reg0("reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
    DCSDisplayNBits disp0("In", 16);
    DCSDisplayNBits disp1("Out", 16);

    inArray.connect(&reg0, {0, 15}, {0, 15});
    inArray.connect(&disp0, {0, 15}, {0, 15});
    inArray.connect(&reg0, {16, 20}, {16, 20}, {"CLK", "R", "S", "LD", "OE"});

    reg0.connect(&disp1);

    //
    //
    uint16_t hcp = reg0.getTimeDelay() / 2 + 2;
    DCSEngine::setHalfClockPeriod(hcp);

    inArray[0]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[1]->makeSignal(transitions{1, 1, 2}, 0, true);
    inArray[2]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[3]->makeSignal(transitions{2, 1, 1}, 0, true);
    inArray[4]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[5]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[6]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[7]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[8]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[9]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[10]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[11]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[12]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[13]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[14]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[15]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[16]->makeSquareWave(hcp, true);
    inArray[17]->makeSignal(0);
    inArray[18]->makeSignal(transitions{6, 1}, 0, true);
    inArray[19]->makeSignal(transitions{1, 3, 1}, 0, true); // LD
    inArray[20]->makeSignal(1);                             // OE

    DCSEngine::run(hcp * 15, false);
}
