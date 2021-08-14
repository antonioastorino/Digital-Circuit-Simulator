
#include "DCSXor.hpp"
#include "DCSCommon.hpp"

DCSXor::DCSXor(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 2;
    numOfOutPins = 1;
}

void DCSXor::updateOut()
{
    uint64_t newOutValue = (in ^ (in >> 1)) & 1;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void xorTest()
{
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
#endif