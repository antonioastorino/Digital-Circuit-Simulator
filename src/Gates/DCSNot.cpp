#include "DCSNot.hpp"

DCSNot::DCSNot(std::string name) :
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 1;
	numOfOutPins = 1;
}

void DCSNot::updateOut() {
	out = !in;
}
