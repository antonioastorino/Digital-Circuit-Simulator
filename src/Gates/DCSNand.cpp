#include "DCSNand.hpp"

DCSNand::DCSNand(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
}

void DCSNand::updateOut(){ out = !((in & (in >> 1)) & 1); }
