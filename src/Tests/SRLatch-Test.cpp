#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSSRLatch.hpp"
#include "DCSEngine.hpp"

void srLatchTest() {
	DCSLog::printTestName("SR-Latch");
	DCSEngine::initialize();
	binary_signal s = {3, 2, 10};
	binary_signal r = {7, 2, 6};
	
	DCSSRLatch SR("Latch1");
	DCSInput I0("In0", s);
	DCSInput I1("In1", r);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&SR, 0, 0, "R");
	I1.connect(&SR, 0, 1, "S");
	SR.connect(&O0, 0, 0, " Q");
	SR.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(11);
}
