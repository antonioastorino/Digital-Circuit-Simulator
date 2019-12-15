//
//  DCSDFlipFlopAsyncSR.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSDFlipFlopAsyncSR::DCSDFlipFlopAsyncSR(std::string name) :
DCSComponent(name, false) {
	node0.connect(&not0, 0, 0);
	node0.connect(&and0, 0, 0);
	not0.connect(&del0, 0, 0);
	del0.connect(&and0, 0, 1);
	and0.connect(&dLatSR0, 0, 1);
}

DCSComponent* DCSDFlipFlopAsyncSR::getOutComponent(ushort &outPinNum) {
	return dLatSR0.getOutComponent(outPinNum);
}

DCSComponent* DCSDFlipFlopAsyncSR::getInComponent(ushort &inPinNum) {
	/*
	 Input pin 1 is the clock, connected to the node at pin 0
	 The other inputs (0, 2, and 3) are mapped by the D-Latch with SR
	 */
	if (inPinNum == 0 || inPinNum == 2 || inPinNum == 3)
		return dLatSR0.getInComponent(inPinNum);
	else if (inPinNum == 1) {
		inPinNum = 0;
		return &node0;
	}
	else exit(-1);
}

void DCSDFlipFlopAsyncSR::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
