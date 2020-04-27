#include "DCSAnd.hpp"
#include "DCSEngine.hpp"
#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void demoTest() {
    DCSLog::printTestName("Demo 1 - And gate");
    {
        // DCSEngine::initialize(1);

        // DCSAnd and0("and0");

        // DCSEngine::run(5);
    }
    {
        DCSEngine::initialize(1);

        DCSInput clk("clk");
        DCSOutput tick("tick");
        clk.makeSquareWave(1);
        clk.connect(&tick, {"CLK"});

		DCSInput in0("a", {1,1}, 0, false);
		DCSInput in1("b", {1,1}, 1, false);
        DCSAnd and0("and0");
        DCSOutput out0("c");

        in0.connect(&and0, 0, 0, "A");
        in1.connect(&and0, 0, 1, "B");
        and0.connect(&out0, {"C"});

        DCSEngine::run(8);
    }
}