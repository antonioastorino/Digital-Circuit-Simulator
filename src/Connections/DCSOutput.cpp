//
//  DCSOutput.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSOutput.hpp"

DCSOutput::DCSOutput(std::string name) :
DCSComponent(name, true) {
	initialized = true; // Ensures no signal propagation from the output
	
	timeDelay = 0;
	numOfInPins = 1;
	numOfOutPins = 0;
}
