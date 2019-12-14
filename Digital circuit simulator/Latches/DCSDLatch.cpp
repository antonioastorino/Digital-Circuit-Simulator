//
//  DCSDLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSDLatch::DCSDLatch(std::string name) :
DCSComponent(name, false) {
	node0.connect(&del0, 0, 0);
	node0.connect(&not0, 0, 0);
	node1.connect(&and0, 0, 1);
	node1.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 0);
	del0.connect(&and1, 0, 1);
	and0.connect(&srLatch0, 0, 0);
	and1.connect(&srLatch0, 0, 1);
}

DCSComponent* DCSDLatch::getOutComponent(ushort &outPinNum) {
	return srLatch0.getOutComponent(outPinNum);
}

DCSComponent* DCSDLatch::getInComponent(ushort &inPinNum) {
	if (inPinNum == 0) return &node0;
	else if (inPinNum == 1) {
		inPinNum = 0; // pin 1 in D latch is EN pin 0
		return &node1;
	}
	else exit(-1);
}

void DCSDLatch::updateOut() {
	throw "This function should never be called";
}
