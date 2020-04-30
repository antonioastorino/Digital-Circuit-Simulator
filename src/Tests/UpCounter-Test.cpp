#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSEngine.hpp"

void upCounterTest() {
	DCSLog::printTestName("Up counter");
	DCSEngine::initialize();
	
	DCSUpCounterWithLoadAndAsyncSR count0("count", 8);
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
	DCSDisplayNBits disp0("In", 8);
	DCSDisplayNBits disp1("Count", 8);

	inArray.connect(&count0, {
		"C_in", "LD", "CLK", "", "",
		"", "", "", "",
		"", "", "", ""});

	count0.connect(&outArray,{
		"","","","",
		"","","","",
		"Cout"});
	
	inArray.connect(&disp0, {5, 12}, {0, 7});
	count0.connect(&disp1, {0, 7}, {0, 7});
	
	uint16_t hp = count0.getTimeDelay()/2+1;
	DCSEngine::setHalfClockPeriod(hp);
	inArray[0]->makeSignal(transitions{2,1}, 0, true);
	inArray[1]->makeSignal(transitions{1,1,1}, 0, true);
	inArray[2]->makeSquareWave(hp);

	inArray[6]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[7]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[8]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[9]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[10]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[11]->makeSignal(transitions{1,1, 1, 1}, 0, true);
	inArray[12]->makeSignal(transitions{1,1, 1, 1}, 0, true);

	DCSEngine::run(300 * hp * 2, true);
}

