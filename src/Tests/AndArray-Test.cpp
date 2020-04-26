#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSEngine.hpp"
#include "DCSAnd.hpp"
#include "DCSComponentArray.hpp"

void andArrayTest() {
	DCSLog::printTestName("Gate array");
	unsigned short hcp = 2;
	DCSEngine::initialize(hcp);
	
	DCSComponentArray<DCSInput> inArray("In", 4);
	DCSComponentArray<DCSAnd> andArray("And", 2);
	DCSDisplayNBits inDisp0("InAnd", 4);
	DCSDisplayNBits outDisp0("OutAnd", 2);

	inArray[0]->makeClock(hcp);
	inArray[1]->makeClock(hcp * 2);
	inArray[2]->makeClock(hcp * 4);
	inArray[3]->makeClock(hcp * 8);
	inArray.connect(&inDisp0);

	inArray.connect(&andArray);
	andArray.connect(&outDisp0);

	DCSEngine::run(2 * hcp * 10);
}
