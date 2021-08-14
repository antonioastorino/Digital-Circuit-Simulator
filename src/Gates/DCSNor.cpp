#include "DCSNor.hpp"
#include "DCSCommon.hpp"

DCSNor::DCSNor(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 2;
    numOfOutPins = 1;
};

void DCSNor::updateOut()
{
    uint64_t newOutValue = !((in | (in >> 1)) & 1);
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}
