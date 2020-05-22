#include "DCSAnd.hpp"

DCSAnd::DCSAnd(std::string name) : DCSComponent(name) {
    this->timeDelay    = 1;
    this->numOfInPins  = 2;
    this->numOfOutPins = 1;
}

void DCSAnd::updateOut() { 
    uint64_t newOutValue = (in & (in >> 1)) & 1;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}
