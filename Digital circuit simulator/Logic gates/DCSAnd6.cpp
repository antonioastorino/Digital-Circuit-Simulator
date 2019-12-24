//
//  DCSAnd6.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSAnd6::DCSAnd6(std::string name):
DCSComponent(name, false),
and3array(name + "-and3array", 2),
and0(name + "-and0") {
	and3array.connect(&and0);
	
	timeDelay = 2;
	numOfInPins = 6;
	numOfOutPins = 1;
}

DCSComponent* DCSAnd6::getOutComponent(ushort &outPinNum) {
	if (outPinNum == 0) return &and0;
	exit(-1);
}

DCSComponent* DCSAnd6::getInComponent(ushort &inPinNum) {
	if (inPinNum < 6) return and3array.getInComponent(inPinNum);
	else exit(-1);
}

void DCSAnd6::updateOut() {
	throw "This function should never be called";
}


