#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSEngine.hpp"

void upCounter4BitsTest() {
	DCSLog::printTestName("Up counter");
	DCSEngine::initialize();
	
	DCSUpCounterWithLoadAndAsyncSR count0("count", 4);
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
	DCSDisplayNBits disp0("In", 4);
	DCSDisplayNBits disp1("Count", 4);

	inArray.connect(&count0, {0, 4}, {0, 4} /*, {"C_in", "LD", "CLK", "", ""}*/);
	inArray.connect(&count0, {5, 8}, {5, 8});

	count0.connect(&outArray,{0,3}, {0,3}, {"C"});
	count0.connect(&outArray,4, 4, {"Cout"});
	
	inArray.connect(&disp0, {5, 8}, {0, 3}, {"I"});
	count0.connect(&disp1, {0, 3}, {0, 3});
	
	uint16_t hp = count0.getTimeDelay()/2+1;

	DCSEngine::setHalfClockPeriod(hp);

	inArray[0]->makeSignal(transitions{2,1}, 0, true);		// Carry in
	inArray[1]->makeSignal(transitions{1,1,1}, 0, true);	// Load
	inArray[2]->makeSquareWave(hp);							// Clock

	inArray[7]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[8]->makeSignal(transitions{1,1, 1, 1}, 0, true);	

	DCSEngine::run(50 * hp * 2, true);
}

