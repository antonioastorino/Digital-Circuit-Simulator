#include "DCSNand3.hpp"

DCSNand3::DCSNand3(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 3;
	numOfOutPins = 1;
}

void DCSNand3::updateOut(){
	out = !((in & (in >> 1) & (in >> 2)) & 1);
}
