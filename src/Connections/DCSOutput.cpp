#include "DCSOutput.hpp"

DCSOutput::DCSOutput(std::string name) :
DCSComponent(name, true) {
	initialized = true; // Ensures no signal propagation from the output
	
	timeDelay = 0;
	numOfInPins = 1;
	numOfOutPins = 0;
}
