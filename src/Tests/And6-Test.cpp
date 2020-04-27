#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"
#include "DCSAnd6.hpp"
#include "DCSComponentArray.hpp"

void and6Test() {
	DCSLog::printTestName("And 6");
	uint16_t hp = 2;
	DCSEngine::initialize(hp);

	DCSComponentArray<DCSInput> inArray("In", 6);
	DCSAnd6 and6_0("And6_0");
	DCSOutput out0("Out0");
	
	inArray.connect(&and6_0, {"I"});
	and6_0.connect(&out0, {"O"});
	
	for (uint16_t i = 0; i < 6; i ++) {
		inArray[i]->makeSquareWave(hp<<i, 0);
	}

	DCSEngine::run(64*hp+1, true);
}

