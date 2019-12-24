//
//  DCSNot.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSNot::DCSNot(std::string name) :
DCSComponent(name) {
	timeDelay = 1;
	numOfInPins = 1;
	numOfOutPins = 1;
}

void DCSNot::updateOut() {
	out = !in;
}
