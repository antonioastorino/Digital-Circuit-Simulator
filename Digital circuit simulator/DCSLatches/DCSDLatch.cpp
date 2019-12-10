//
//  DCSDLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSDLatch.hpp"

DCSDLatch::DCSDLatch(std::string name) :
DCSComponent(name, 1, 2, false) {
	node0.connect(&and1, 0, 1);
	node0.connect(&not0, 0, 0);
	node1.connect(&and0, 0, 1);
	node1.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 0);
	and0.connect(&srLatch0, 0, 0);
	and1.connect(&srLatch0, 0, 1);
	srLatch0.setParent(this);
}

DCSComponent* DCSDLatch::getOutComponent(int &outPinNum) {
	return srLatch0.getOutComponent(outPinNum);
}

DCSComponent* DCSDLatch::getInComponent(int &inPinNum) {
	if (inPinNum == 0) return &node0;
	else if (inPinNum == 1) {
		inPinNum = 0; // pin 1 in D latch is EN pin 0
		return &node1;
	}
	else exit(-1);
}

void DCSDLatch::updateOut() {
	out = srLatch0.getOutVal(0) + (srLatch0.getOutVal(1) << 1);
	updateParentOut();
}
