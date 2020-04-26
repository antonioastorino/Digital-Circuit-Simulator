
#include "DCSOr.hpp"

DCSOr::DCSOr(std::string name):
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
}

void DCSOr::updateOut(){
	out = (in | (in >> 1)) & 1;
}
