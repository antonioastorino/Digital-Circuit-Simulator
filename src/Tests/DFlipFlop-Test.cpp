#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSEngine.hpp"

void dFlipFlopTest() {
	DCSLog::printTestName("D-FlipFlop");
	DCSEngine::initialize();
	binary_signal d = {4, 7, 3, 10};
	binary_signal clk = {4, 2, 5, 2, 4};

	DCSDFlipFlop dff0("DFF0");
	DCSInput I0("In0", d);
	DCSInput I1("In1", clk);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");

	I0.connect(&dff0, 0, 0, "DATA");
	I1.connect(&dff0, 0, 1, "CLK");
	dff0.connect(&O0, 0, 0, " Q");
	dff0.connect(&O1, 1, 0, "!Q");

	DCSEngine::run(20);
}
