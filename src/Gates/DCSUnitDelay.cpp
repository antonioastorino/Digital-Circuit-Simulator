//
//  DCSUnitDelay.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSUnitDelay.hpp"

DCSUnitDelay::DCSUnitDelay(std::string name) :
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 1;
	numOfOutPins = 1;
}

void DCSUnitDelay::updateOut() { out = in; }
