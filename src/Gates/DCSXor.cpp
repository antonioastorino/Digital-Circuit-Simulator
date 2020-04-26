
#include "DCSXor.hpp"

DCSXor::DCSXor(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
}

void DCSXor::updateOut(){
	out = (in ^ (in >> 1)) & 1;
}
