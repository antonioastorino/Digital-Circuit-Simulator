#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSEngine.hpp"
#include "DCSComponentArray.hpp"

void displayTest() {
	DCSLog::printTestName("Display");
	unsigned short hp = 1;
	DCSEngine::reset(hp);
	
	DCSComponentArray<DCSInput> inArray("In", 8);
	
	DCSDisplayNBits disp0("Display", 8);
	
	inArray[0]->makeClock(1,0);
	inArray[1]->makeClock(1,0);
	inArray.connect(&disp0);
	
	DCSEngine::run(10, false);
}
