#include "DCSNor.hpp"

DCSNor::DCSNor(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
};

void DCSNor::updateOut(){
	out = !((in | (in >> 1)) & 1);
}
