#include "test-AndArray.hpp"

void andArrayTest() {
	DCSLog::printTestName("And array");
	uint16_t hcp = 2;
	DCSEngine::initialize(hcp);
	
	DCSComponentArray<DCSInput> inArray("In", 4);
	DCSComponentArray<DCSAnd> andArray("And", 2);
	DCSDisplayNBits inDisp0("InAnd", 4);
	DCSDisplayNBits outDisp0("OutAnd", 2);

	inArray[0]->makeSquareWave(hcp);
	inArray[1]->makeSquareWave(hcp * 2);
	inArray[2]->makeSquareWave(hcp * 4);
	inArray[3]->makeSquareWave(hcp * 8);
	inArray.connect(&inDisp0);

	inArray.connect(&andArray);
	andArray.connect(&outDisp0);

	DCSEngine::run(2 * hcp * 10);
}
