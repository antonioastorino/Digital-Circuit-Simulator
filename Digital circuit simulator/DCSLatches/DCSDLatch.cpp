//
//  DCSDLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSDLatch.hpp"

DCSDLatch::DCSDLatch() : DCSComponent(1, 2, false) {
	D.connect(&and1, 0, 1);
	D.connect(&not0, 0, 0);
	EN.connect(&and0, 0, 1);
	EN.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 0);
	and0.connect(&srLatch0, 0, 0);
	and1.connect(&srLatch0, 0, 1);
//	not0.setParent(this);
//	and0.setParent(this);
//	and1.setParent(this);
	srLatch0.setParent(this);
}

DCSComponent* DCSDLatch::getOutComponent(int &outPinNum) {
	return srLatch0.getOutComponent(outPinNum);
}

DCSComponent* DCSDLatch::getInComponent(int &inPinNum) {
	if (inPinNum == 0) return &D;
	else if (inPinNum == 1) {
		inPinNum = 0; // pin 1 in D latch is EN pin 0
		return &EN;
	}
	else exit(-1);
}

void DCSDLatch::updateOut() {
	out = srLatch0.getOutVal(0) + (srLatch0.getOutVal(1) << 1);
	updateParentOut();
}
