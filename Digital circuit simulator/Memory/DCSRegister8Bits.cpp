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
registerArray(name, 8),
nodeArray({"Load", "Clock", "Clear", "Preset"}, 4) {
	for (ushort i = 0; i < 8; i++) {
		nodeArray[0]->connect(registerArray[i], 0, 4); // Load
		nodeArray[1]->connect(registerArray[i], 0, 1); // Clock
		nodeArray[2]->connect(registerArray[i], 0, 2); // Clear
		nodeArray[3]->connect(registerArray[i], 0, 3); // Preset
	}
}

DCSComponent* DCSRegister8Bits::getOutComponent(ushort &outPinNum) {
	if (outPinNum >= 8) {
		DCSLog::error(name, "Pin out of range");
		exit(-1);
	}
	ushort elementNumber = outPinNum;
	outPinNum = 0;
	return registerArray[elementNumber]->getOutComponent(outPinNum);
}

DCSComponent* DCSRegister8Bits::getInComponent(ushort &inPinNum) {
	if (inPinNum < 4) {
		ushort elementNumber = inPinNum;
		inPinNum = 0;
		return nodeArray[elementNumber]->getInComponent(inPinNum);
	}
	else if (inPinNum < 12) {
		ushort elementNumber = inPinNum - 4;
		inPinNum = 0;
		return registerArray[elementNumber]->getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

void DCSRegister8Bits::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
