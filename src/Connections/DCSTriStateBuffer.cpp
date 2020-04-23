//
//  DCSTriStateBuffer.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSTriStateBuffer::DCSTriStateBuffer(std::string name) :
DCSComponent(name) {
	isTristate = true;
	enabled = false; // disabled by default
	
	timeDelay = 1;
	numOfInPins = 2;
	numOfOutPins = 1;
}

void DCSTriStateBuffer::updateOut() {
	if ((in >> 1) & 1) {
		enable();
		
		out = in & 1;
//		updateParentOut();
	}
	else { disable(); }
}

void DCSTriStateBuffer::enable(){ enabled = true; }
void DCSTriStateBuffer::disable(){ enabled = false; }
