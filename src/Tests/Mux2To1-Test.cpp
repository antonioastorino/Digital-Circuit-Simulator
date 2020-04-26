#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSMux2to1.hpp"
#include "DCSEngine.hpp"

void mux2To1Test() {
	DCSLog::printTestName("Mux 2 to 1");
	uint16_t hp = 3;
	DCSEngine::initialize(hp);
	
	DCSMux2to1 mux0("Mux0");
	
	DCSInput in0("In0");
	DCSInput in1("In1");
	DCSInput in2("Sel0");
	
	DCSOutput out0("Out0");
	
	in0.connect(&mux0, 0, 0, "I0");
	in1.connect(&mux0, 0, 1, "I1");
	in2.connect(&mux0, 0, 2, "SEL");
	
	mux0.connect(&out0, 0,0, "OUT");

	/*
	 Expected result:
	I0 I1 SEL OUT    0
	 1  1   1   0    0
	 1  1   0   1    3
	 0  1   1   1    6
	 0  1   0   1    9
	 1  0   1   0    12
	 1  0   0   0    15
	 0  0   1   1    18
	 0  0   0   0    21
	 1  1   1   0    24
	 */
	in0.makeClock(hp * 2);
	in1.makeClock(hp * 4);
	in2.makeClock();

	
	DCSEngine::run(hp * 9, true);
}
