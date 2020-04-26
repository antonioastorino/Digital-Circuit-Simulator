#include "DCSAnd.hpp"

DCSAnd::DCSAnd(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
}

void DCSAnd::updateOut(){ out = (in & (in >> 1)) & 1; }
