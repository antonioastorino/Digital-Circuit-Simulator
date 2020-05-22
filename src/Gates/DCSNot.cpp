#include "DCSNot.hpp"

DCSNot::DCSNot(std::string name) : DCSComponent(name) {
    timeDelay    = 1;
    numOfInPins  = 1;
    numOfOutPins = 1;
}

void DCSNot::updateOut() {
    uint64_t newOutValue = !in;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}
