#include "DCSTriStateBuffer.hpp"

DCSTriStateBuffer::DCSTriStateBuffer(std::string name) :
DCSComponent(name) {
	tristate = true;
	enabled = false; // disabled by default
	
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
}

void DCSTriStateBuffer::updateOut() {
	if ((in >> 1) & 1) {
		enable();
		out = in & 1;
	}
	else { disable(); }
}

void DCSTriStateBuffer::enable(){ enabled = true; }
void DCSTriStateBuffer::disable(){ enabled = false; }
