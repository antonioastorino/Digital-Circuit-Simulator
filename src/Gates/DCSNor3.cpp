#include "DCSNor3.hpp"

DCSNor3::DCSNor3(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 3;
	numOfOutPins = 1;
};

void DCSNor3::updateOut(){
	out = !((in | (in >> 1) | (in >> 2)) & 1);
}
