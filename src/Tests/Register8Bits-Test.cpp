#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSEngine.hpp"

void register8BitsTest() {
	DCSLog::printTestName("8-bit register");
	DCSEngine::initialize();
	
	DCSRegister8Bits reg0("reg0");
	DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", reg0.getNumOfOutPins());
	
//	inArray.connect(&count0, {
//		"C_in", "LD", "CLK", "R", "S",
//		"I0", "I1", "I2", "I3"});
	inArray.connect(&reg0, {
		"OE", "CLK", "R", "S", "LD",
		"I", "I", "I", "I",
		"I", "I", "I", "I"});

	reg0.connect(&outArray,{
		" O0","O1","O2","O3",
		"O4","O5","O6","O7"});
	
//
//
	uint16_t clkHalfPeriod = reg0.getTimeDelay()/2+4;
	DCSEngine::setHalfClockPeriod(clkHalfPeriod);
	
	inArray[0]->makeSignal(transitions{3,1}, 0, true); // OE
	inArray[1]->makeSquareWave(1);
	inArray[2]->makeSignal(0);
	inArray[3]->makeSignal(transitions{5,1}, 0, true);
	inArray[4]->makeSignal(transitions{1,3,1}, 0, true); // LD
	inArray[5]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[6]->makeSignal(transitions{1,1, 2}, 0, true);
	inArray[7]->makeSignal(transitions{1,1, 1, 1}, 0,true);
	inArray[8]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[9]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[10]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[11]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[12]->makeSignal(transitions{1,1, 1, 1}, 0, true);
//	inArray[4]->makeSignal(0);
//	inArray[5]->makeSignal(0);
//
//
//	div0.connect(&outArray, {"Q", "!Q", "C_out"});
//
	DCSEngine::run(clkHalfPeriod * 20);
}
