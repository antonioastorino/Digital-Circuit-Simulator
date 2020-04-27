#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"
#include "DCSOr.hpp"
#include "DCSComponentArray.hpp"

void orTest() {
	DCSLog::printTestName("Or");
	DCSEngine::initialize(1);
	
	DCSComponentArray<DCSInput> inArray("In", 2);
	DCSOr or0("Or0");
	DCSOutput out0("Out0");
	
	transitions in0 = {2,2,4,10};
	transitions in1 = {4,2,2,10};
	
	inArray[0]->makeSquareWave(1);
	inArray[1]->makeSquareWave(2);
	
	inArray.connect(&or0, 0, 0, "A");
	inArray.connect(&or0, 1, 1, "B");
	or0.connect(&out0, 0, 0, "AorB");
	
	DCSEngine::run(5);
}
