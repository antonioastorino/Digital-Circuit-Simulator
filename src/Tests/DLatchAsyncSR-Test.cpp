#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSEngine.hpp"
#include "DCSComponentArray.hpp"

void dLatchAsyncSRTest() {
	DCSLog::printTestName("D-Latch with asynchronous SR");
	DCSEngine::initialize(5);
	transitions d = {10,3,3,4};
	transitions en = {2,2,7,2,4};
	transitions reset = {18,2,5};

	
	DCSDLatchAsyncSR dLatch0("DLatch0");
	DCSComponentArray<DCSInput> inArray("In", 4);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	inArray.connect(&dLatch0, 0, 0, "DATA");
	inArray.connect(&dLatch0, 1, 1, "EN");
	inArray.connect(&dLatch0, 2, 2, "R");
	inArray.connect(&dLatch0, 3, 3, "S");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	inArray[0]->makeSignal(d);
	inArray[1]->makeSignal(en);
	inArray[2]->makeSignal(reset);
	inArray[3]->makeSignal(0);

	DCSEngine::run(25);
}
