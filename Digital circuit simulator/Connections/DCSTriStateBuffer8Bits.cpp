//
//  DCSTriStateBuffer8Bits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSTriStateBuffer8Bits::DCSTriStateBuffer8Bits(std::string name):
DCSComponent(name, false),
bufferArray(name, 8),
node0(name + "-Enable") {
	// Connect global enable to that of all buffers
	for (ushort i = 0; i < 8; i++) {
		node0.connect(bufferArray[i], 0, 1);
	}
	
	timeDelay = 1;
	numOfInPins = 9;
	numOfOutPins = 8;
}

DCSComponent* DCSTriStateBuffer8Bits::getInComponent(ushort &inPinNum) {
	if (inPinNum == 0) {
		return &node0;
	}
	else if (inPinNum < 9) {
		ushort elementNumber = inPinNum - 1;
		inPinNum = 0;
		// TODO: check if the buffer element can be directly returned
		return bufferArray[elementNumber]->getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

DCSComponent* DCSTriStateBuffer8Bits::getOutComponent(ushort &outPinNum) {
	if (outPinNum >= 8) {
		DCSLog::error(name, "Pin out of range");
		exit(-1);
	}
	ushort elementNumber = outPinNum;
	outPinNum = 0;
	return bufferArray[elementNumber]->getOutComponent(outPinNum);
}

void DCSTriStateBuffer8Bits::enable() {
	for (ushort i = 0; i < 8; i++) {
		bufferArray[i]->enable();
	}
}

void DCSTriStateBuffer8Bits::disable() {
	for (ushort i = 0; i < 8; i++) {
		bufferArray[i]->disable();
	}
}

void DCSTriStateBuffer8Bits::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
