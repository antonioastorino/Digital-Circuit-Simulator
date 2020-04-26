#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"
#include "DCSAnd6.hpp"
#include "DCSComponentArray.hpp"

void and6Test() {
	DCSLog::printTestName("And 6");
	unsigned short hp = 2;
	DCSEngine::reset(hp);

	DCSComponentArray<DCSInput> inArray("In", 6);
	DCSAnd6 and6_0("And6_0");
	DCSOutput out0("Out0");
	
	inArray.connect(&and6_0, {"I"});
	and6_0.connect(&out0, {"O"});
	
	for (unsigned short i = 0; i < 6; i ++) {
		inArray[i]->makeClock(hp<<i, 0);
	}

	DCSEngine::run(64*hp+1, true);
}

