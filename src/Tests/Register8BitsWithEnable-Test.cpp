#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8BitsWithEnable.hpp"

void register8BitsWithEnableTest() {
    DCSLog::printTestName("8-bit register with enable");
    DCSEngine::initialize(1);

    DCSRegister8BitsWithEnable reg0("reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
    DCSDisplayNBits disp0("In", 8);
    DCSDisplayNBits disp1("Out", 8);

    inArray.connect(&reg0, {0, 7}, {0, 7});
    inArray.connect(&disp0, {0, 7}, {0, 7});
    inArray.connect(&reg0, {8, 12}, {8, 12}, {"CLK", "R", "S", "LD", "OE"});

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
    inArray[5]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[6]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[7]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[8]->makeSquareWave(hcp, true);
    inArray[9]->makeSignal(0);
    inArray[10]->makeSignal(transitions{6, 1}, 0, true);
    inArray[11]->makeSignal(transitions{1, 3, 1}, 0, true); // LD
    inArray[12]->makeSignal(1);                             // OE
    // inArray[12]->makeSignal(transitions{3, 1}, 0, true); // OE

    DCSEngine::run(hcp * 15, false);
}
