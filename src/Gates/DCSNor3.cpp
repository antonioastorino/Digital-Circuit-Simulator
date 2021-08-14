#include "DCSNor3.hpp"
#include "DCSCommon.hpp"

DCSNor3::DCSNor3(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 3;
    numOfOutPins = 1;
};

void DCSNor3::updateOut()
{
    uint64_t newOutValue = !((in | (in >> 1) | (in >> 2)) & 1);
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void nor3Test()
{
    DCSLog::printTestName("Nor 3");
    DCSEngine::initialize(1);

    DCSComponentArray<DCSInput> inArray("In", 3);
    DCSNor3 nor30("Nor30");
    DCSOutput out0("Out0");

    inArray[0]->makeSquareWave(1, 0);
    inArray[1]->makeSquareWave(2, 0);
    inArray[2]->makeSquareWave(4, 0);

    inArray.connect(&nor30, 0, 0, "A");
    inArray.connect(&nor30, 1, 1, "B");
    inArray.connect(&nor30, 2, 2, "C");
    nor30.connect(&out0, 0, 0, "Nor");

    DCSEngine::run(9);
}
#endif