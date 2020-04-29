#include "DCSAnd.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSOutput.hpp"
#include "DCSTriStateBuffer.hpp"

void demoTest() {
    /*
        DCSLog::printTestName("Demo - I/O");
        {
            // Engine initialization
            DCSEngine::initialize(1);

            // Instantiation
            DCSInput in0("I");
            DCSOutput out0("O");

            // Signal definition
            // No definition means constant signals at 0

            // Connection
            in0.connect(&out0, {"I/O"});

            // Run
            DCSEngine::run(5);
        }//*/

    /*
    DCSLog::printTestName("Demo - And");
    {
        // Engine initialization
        DCSEngine::initialize(1);

        // Instantiation circuit 1
        DCSInput clk("clk");
        DCSOutput tick("tick");

        // Signal definition
        clk.makeSquareWave(1);
        clk.connect(&tick, {"CLK"});

        // Signal definition
        DCSInput in0("a");
        DCSInput in1("b");

        in0.makeSignal({1, 1}, 0, false);
        in1.makeSignal({1, 1}, 1, false);

        DCSAnd and0("and0");
        DCSOutput out0("c");

        // Signal definition
        in0.connect(&and0, 0, 0, "A");
        in1.connect(&and0, 0, 1, "B");
        and0.connect(&out0, {"C"});

        DCSEngine::run(8);
    }//*/

    /*
    DCSLog::printTestName("Demo - Missing connections");
    {
        DCSEngine::initialize(1);

        DCSAnd and0("and0");

        DCSEngine::run(5);
    }//*/

    /*
    DCSLog::printTestName("Demo - Loop");
    {
        DCSEngine::initialize(1);

        DCSNot not0("not0");
        not0.connect(&not0, {"b"});

        DCSEngine::run(5);
    }//*/
    DCSLog::printTestName("Demo - Tri-state buffer");

    {
        DCSEngine::initialize();

        DCSInput inA0("in0", 0);
        DCSInput inA1("c0");
        DCSInput inB0("in1", 1);
        DCSInput inB1("c1");
        DCSTriStateBuffer tsbA("tsbA");
        DCSTriStateBuffer tsbB("tsbB");
        DCSNode node0("node0");
        DCSOutput out0("Out0");

        inA1.makeSignal({2, 2, 2, 2, 2, 1, 1}, 1, false);
        inB1.makeSignal({2, 2, 2, 2, 2, 2, 1}, 0, false);

        inA0.connect(&tsbA, 0, 0, "in0");
        inA1.connect(&tsbA, 0, 1, "C0");
        inB0.connect(&tsbB, 0, 0, "in1");
        inB1.connect(&tsbB, 0, 1, "C1");
        tsbA.connect(&node0, 0, 0, "trisA");
        tsbB.connect(&node0, 0, 0, "trisB");
        node0.connect(&out0, 0, 0, "Out");

        DCSEngine::run(20);
    }
}
