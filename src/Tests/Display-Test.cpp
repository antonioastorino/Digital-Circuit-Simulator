#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSEngine.hpp"
#include "DCSComponentArray.hpp"

void displayTest() {
	DCSLog::printTestName("Display");
	uint16_t hp = 1;
	DCSEngine::initialize(hp);
	
	DCSComponentArray<DCSInput> inArray("In", 8);
	
	DCSDisplayNBits disp0("Display", 8);
	
	inArray[0]->makeSquareWave(1,0);
	inArray[1]->makeSquareWave(1,0);
	inArray.connect(&disp0);
	
	DCSEngine::run(10, false);
}
