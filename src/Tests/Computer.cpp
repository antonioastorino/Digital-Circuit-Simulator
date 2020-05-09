#include "DCSAnd.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSTriStateBuffer.hpp"

void Computer() {
    DCSLog::printTestName("Computer");
    {
        DCSEngine::initialize(1);

        // bus
        DCSComponentArray<DCSNode> bus("bus", 8);

        // input array for reg A
        DCSComponentArray<DCSInput> inA("inA", 8);
        DCSInput oeA("oaA");
        DCSInput clkA("clkA");
        DCSInput presA("presA");
        DCSInput resA("resA");
        DCSInput loadA("loadA");

        // register A
        DCSRegister8Bits regA("regA");

        // register A display
        DCSDisplayNBits dispA("outA", 8);

        // connections
        inA.connect(&regA, {0, 7}, {5, 12});
        regA.connect(&bus);
        regA.connect(&dispA);
        oeA.connect(&regA, 0, 0, "oaA");
        clkA.connect(&regA, 0, 1, "oaA");
        presA.connect(&regA, 0, 2, "oaA");
        resA.connect(&regA, 0, 3, "oaA");
        loadA.connect(&regA, 0, 4, "oaA");

        DCSEngine::run(20);
    }
}
