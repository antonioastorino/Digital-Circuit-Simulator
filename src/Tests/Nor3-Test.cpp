#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"
#include "DCSNor3.hpp"
#include "DCSComponentArray.hpp"

void nor3Test() {
	DCSLog::printTestName("Nor 3");
	DCSEngine::initialize(1);
	
	DCSComponentArray<DCSInput> inArray("In", 3);
	DCSNor3 nor30("Nor30");
	DCSOutput out0("Out0");

	inArray[0]->makeSquareWave(1, 0);
	inArray[1]->makeSquareWave(2, 0);
	inArray[2]->makeSquareWave(4, 0);

	inArray.connect(&nor30, 0, 0, "A");
	inArray.connect(&nor30, 1, 1, "B");
	inArray.connect(&nor30, 2, 2, "C");
	nor30.connect(&out0, 0, 0, "Nor");
	
	DCSEngine::run(9);
}
