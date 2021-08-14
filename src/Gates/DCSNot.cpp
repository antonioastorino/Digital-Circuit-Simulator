#include "DCSNot.hpp"
#include "DCSCommon.hpp"

DCSNot::DCSNot(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 1;
    numOfOutPins = 1;
}

void DCSNot::updateOut()
{
    uint64_t newOutValue = !in;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSLog.hpp"

void notLoopTest()
{
    DCSLog::printTestName("Not loop");
    DCSEngine::initialize(5);
    DCSNot not0("Not0");
    DCSNot not1("Not1");
    DCSNot not2("Not2");

    not0.connect(&not1, 0, 0, "N0");
    not1.connect(&not2, 0, 0, "N1");
    not2.connect(&not0, 0, 0, "N2");

    DCSEngine::run(11);
}
#endif