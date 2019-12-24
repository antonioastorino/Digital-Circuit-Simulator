//
//  DCSRegister8Bits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 17/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSRegister8Bits::DCSRegister8Bits(std::string name) :
DCSComponent(name, false),
registerArray(name + "-reg", 8),
nodeArray({"OutEnable", "Clock", "Clear", "Preset", "Load"}, 5) {
	// connect control signals
	for (ushort i = 0; i < 8; i++) {
		nodeArray.connect(registerArray[i], 0, 0);
		nodeArray.connect(registerArray[i], 1, 1);
		nodeArray.connect(registerArray[i], 2, 2);
		nodeArray.connect(registerArray[i], 3, 3);
		nodeArray.connect(registerArray[i], 4, 4);
	}
	
	timeDelay = registerArray[0]->getTimeDelay();
	numOfInPins = 13;
	numOfOutPins = 8;
}

DCSComponent* DCSRegister8Bits::getOutComponent(ushort &outPinNum) {
	if (outPinNum < 8) {
		return registerArray.getOutComponent(outPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

DCSComponent* DCSRegister8Bits::getInComponent(ushort &inPinNum) {
	if (inPinNum < 5) {
		return nodeArray.getInComponent(inPinNum);
	}
	else if (inPinNum < 13) {
		ushort elementNumber = inPinNum - 5;
		inPinNum = 5;
		return registerArray[elementNumber]->getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

void DCSRegister8Bits::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
