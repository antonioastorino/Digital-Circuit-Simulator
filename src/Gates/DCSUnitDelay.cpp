#include "DCSUnitDelay.hpp"
#include "DCSCommon.hpp"

DCSUnitDelay::DCSUnitDelay(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 1;
    numOfOutPins = 1;
}

void DCSUnitDelay::updateOut()
{
    uint64_t newOutValue = in;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSLog.hpp"
#include "DCSNot.hpp"

void unitDelayTest()
{
    DCSLog::printTestName("Unit delay");
    DCSEngine::initialize(5);
    DCSNot not0("Not0");
    DCSUnitDelay del0("Del0");

    not0.connect(&del0, {"N0"});
    del0.connect(&not0, {"D0"});

    DCSEngine::run(11);
}
#endif