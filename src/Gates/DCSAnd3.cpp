#include "DCSAnd3.hpp"

DCSAnd3::DCSAnd3(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 3;
    numOfOutPins = 1;
}

void DCSAnd3::updateOut() { out = (in & (in >> 1) & (in >> 2)) & 1; }
