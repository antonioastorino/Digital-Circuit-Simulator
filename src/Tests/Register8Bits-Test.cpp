#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSDisplayNBits.hpp"

void register8BitsTest() {
    DCSLog::printTestName("8-bit register");
    DCSEngine::initialize(1);

    DCSRegister8Bits reg0("reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
	DCSDisplayNBits disp0("In", 8);
	DCSDisplayNBits disp1("Out", 8);

    //	inArray.connect(&count0, {
    //		"C_in", "LD", "CLK", "R", "S",
    //		"I0", "I1", "I2", "I3"});
    inArray.connect(&reg0, {0, 4}, {0, 4}, {"OE", "CLK", "R", "S", "LD"});
    inArray.connect(&reg0, {5, 12}, {5, 12});
	inArray.connect(&disp0, {5, 12}, {0, 7});

    reg0.connect(&disp1);

    //
    //
    uint16_t hcp = reg0.getTimeDelay() / 2 + 4;
    DCSEngine::setHalfClockPeriod(hcp);

    inArray[0]->makeSignal(transitions{3, 1}, 0, true); // OE
    inArray[1]->makeSquareWave(hcp);
    inArray[2]->makeSignal(0);
    inArray[3]->makeSignal(transitions{5, 1}, 0, true);
    inArray[4]->makeSignal(transitions{1, 3, 1}, 0, true); // LD
    inArray[5]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[6]->makeSignal(transitions{1, 1, 2}, 0, true);
    inArray[7]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[8]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[9]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[10]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[11]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[12]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    //	inArray[4]->makeSignal(0);
    //	inArray[5]->makeSignal(0);
    //
    //
    //	div0.connect(&outArray, {"Q", "!Q", "C_out"});
    //
    DCSEngine::run(hcp * 20, true);
}
