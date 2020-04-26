#include "DCSUnitDelay.hpp"

DCSUnitDelay::DCSUnitDelay(std::string name) :
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 1;
	numOfOutPins = 1;
}

void DCSUnitDelay::updateOut() { out = in; }
