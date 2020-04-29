#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSFullAdder.hpp"
#include "DCSEngine.hpp"

void fullAdderTest() {
	DCSLog::printTestName("Full adder");
	uint16_t hp = 10;
	DCSEngine::initialize(hp);
	
	DCSFullAdder fa0("FA0");
	
	DCSInput in0("A");
	DCSInput in1("B");
	DCSInput in2("Cin");
	
	DCSOutput out0("Sum");
	DCSOutput out1("Cout");

	in0.connect(&fa0, 0, 0, "A");
	in1.connect(&fa0, 0, 1, "B");
	in2.connect(&fa0, 0, 2, "Cin");
	
	fa0.connect(&out0, 0,0, "Sum");
	fa0.connect(&out1, 1,0, "Cout");

	in0.makeSquareWave(hp * 2);
	in1.makeSquareWave(hp * 4);
	in2.makeSquareWave(hp);

	DCSEngine::run(hp * 9, false);
}
