#include "DCSAnd.hpp"

DCSAnd::DCSAnd(std::string name) : DCSComponent(name) {
    this->timeDelay    = 1;
    this->numOfInPins  = 2;
    this->numOfOutPins = 1;
}

void DCSAnd::updateOut() { out = (in & (in >> 1)) & 1; }
