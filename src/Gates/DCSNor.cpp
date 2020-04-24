//
//  DCSNor.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 26/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
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
