#include "DCSAnd4.hpp"

DCSAnd4::DCSAnd4(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 4;
    numOfOutPins = 1;
}

void DCSAnd4::updateOut()
{
    uint64_t newOutValue = (in & (in >> 1) & (in >> 2) & (in >> 3)) & 1;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}
