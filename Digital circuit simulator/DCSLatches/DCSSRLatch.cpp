//
//  DCSSRLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSSRLatch.hpp"

DCSSRLatch::DCSSRLatch() : DCSComponent(2, 2, false) {
	nor0.connect(&nor1, /*out*/ 0, /*in*/ 0, "Q");
	nor1.connect(&nor0, /*out*/ 0, /*in*/ 1, "!Q");
}

void DCSSRLatch::setIn(bool* inVec) {
	// Update component input
	DCSComponent::setIn(inVec);
	// Update internal components' input
	nor0.setIn(inVec[0], 0);
	nor1.setIn(inVec[1], 1);
}

void DCSSRLatch::setIn(bool inVal, int inPinNum) {
	// Update component input
	in[inPinNum] = inVal;
	// Update internal components' input
	if (inPinNum == 0) nor0.setIn(inVal, 0);
	else if (inPinNum == 1) nor1.setIn(inVal, 1);
};

void DCSSRLatch::updateOut() {
	out[0] = nor0.getOutVal(0); // Q
	out[1] = nor1.getOutVal(0); // !Q
}
