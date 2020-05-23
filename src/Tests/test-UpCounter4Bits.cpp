#include "test-UpCounter4Bits.hpp"

void upCounter4BitsTest() {
	DCSLog::printTestName("Up counter");
	DCSEngine::initialize(5);
	
	DCSUpCounterWithLoadAndAsyncSR count0("count", 4);
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
	DCSDisplayNBits disp0("In", 4);
	DCSDisplayNBits disp1("Count", 4);

	// connect control signals
	inArray.connect(&count0, {0, 4}, {0, 4}, {"C_in", "LD", "CLK", "", ""});
	
	// connect data-in signals
	inArray.connect(&count0, {5, 8}, {5, 8});

	// connect data-in to display (for enhanced visualization purposes)
	inArray.connect(&disp0, {5, 8}, {0, 3});

	// connect counter output to output object
	count0.connect(&outArray,{0,3}, {0,3});
	count0.connect(&outArray,4, 4, {"Cout"});
	
	
	count0.connect(&disp1, {0, 3}, {0, 3});
	
	uint16_t hp = count0.getTimeDelay()/2+1;

	DCSEngine::setHalfClockPeriod(hp);

	inArray[0]->makeSignal(transitions{4,1}, 0, true);		// Carry in
	inArray[1]->makeSignal(transitions{1,1,1}, 0, true);	// Load
	inArray[2]->makeSquareWave(hp);							// Clock

	inArray[7]->makeSignal(transitions{1,1, 1}, 0, true);
	inArray[8]->makeSignal(transitions{1,1, 1}, 0, true);	

	DCSEngine::run(50 * hp * 2, true);
}

