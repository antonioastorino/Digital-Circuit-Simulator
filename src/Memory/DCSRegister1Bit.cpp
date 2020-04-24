//
//  DCSRegister1Bit.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSRegister8Bits.hpp"

DCSRegister1Bit::DCSRegister1Bit(std::string name) :
DCSComponent(name, false),
node0(name + "-Load"),
not0(name + "-Data"),
and0(name + "-And0"),
and1(name + "-And1"),
or0(name + "-Or0"),
tris0(name + "-OutTris"),
dffsr0(name + "DFFSR0") {
	node0.connect(&not0, 0, 0);
	node0.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 1);
	dffsr0.connect(&and0, 0, 0);
	dffsr0.connect(&tris0, 0, 0); // tri-state buffer
	and0.connect(&or0, 0, 0);
	and1.connect(&or0, 0, 1);
	or0.connect(&dffsr0, 0, 0);
	
	timeDelay = 7;
	numOfInPins = 6;
	numOfOutPins = 1;
}

DCSComponent* DCSRegister1Bit::getOutComponent(ushort &outPinNum) {
	if (outPinNum == 0)	return &tris0;
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

DCSComponent* DCSRegister1Bit::getInComponent(ushort &inPinNum) {
	switch (inPinNum) {
		case 0: // Tris-state OE
			inPinNum = 1;
			return &tris0;
			break;
		case 1: // Clock
			return dffsr0.getInComponent(inPinNum);
			break;
		case 2:  // Clear
			return dffsr0.getInComponent(inPinNum);
			break;
		case 3:  // Preset
			return dffsr0.getInComponent(inPinNum);
			break;
		case 4:  // Load
			inPinNum = 0;
			return &node0;
		case 5:
			inPinNum = 1;
			return &and1;
			break;
		default:
			break;
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}
void DCSRegister1Bit::updateOut() {
	DCSLog::error(name, "This function should never be called");
}

