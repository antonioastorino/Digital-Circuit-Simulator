#include "DCSNand.hpp"

DCSNand::DCSNand(std::string name) : DCSComponent(name) {
    timeDelay    = 1;
    numOfInPins  = 2;
    numOfOutPins = 1;
}

void DCSNand::updateOut() {
    uint64_t newOutValue = !((in & (in >> 1)) & 1);
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}