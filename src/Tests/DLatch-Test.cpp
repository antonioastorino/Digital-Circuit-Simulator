#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSDLatch.hpp"
#include "DCSEngine.hpp"

void dLatchTest() {
	DCSLog::printTestName("D-Latch");
	DCSEngine::initialize();
	
	DCSDLatch dLatch0("DLatch0");
	DCSInput I0("In0");
	DCSInput I1("In1");

	I0.makeSignal({3,7,3,3,3}, 0, false);
	I1.makeSignal({4,2,5,2,6}, 0, false);
	
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&dLatch0, 0, 0, "DATA");
	I1.connect(&dLatch0, 0, 1, "EN");
	
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(20);
}
