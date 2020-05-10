#include "DCSComponentArray.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSNode.hpp"
#include "DCSOutput.hpp"
#include "DCSXor.hpp"

void xorTest() {
    DCSLog::printTestName("Xor");
    DCSEngine::initialize(1);

    DCSInput in0("In");
    DCSXor xor0("xors");
    DCSOutput out0("out0");
    DCSInput inSU("inSU");

    in0.connect(&xor0, 0, 0, "In0");
    inSU.connect(&xor0, 0, 1, "SU");

    xor0.connect(&out0, 0, 0, "out0");

    in0.makeSquareWave(2);
	inSU.makeSquareWave(4);

    DCSEngine::run(8);
}
