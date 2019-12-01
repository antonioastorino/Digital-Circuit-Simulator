//
//  DCSSRLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSSRLatch.hpp"
#include "DCSEngine.hpp"
#include <iostream>

DCSSRLatch::DCSSRLatch() : DCSComponent(2, 2, false) {
	nor0.connect(&nor1, /*out*/ 0, /*in*/ 0, " Q");
	nor1.connect(&nor0, /*out*/ 0, /*in*/ 1, "!Q");
	nor0.setParent(this);
	nor1.setParent(this);
}

DCSComponent* DCSSRLatch::getLeftComponent(int outPinNum) {
	if (outPinNum == 0) return &nor0;
	else if (outPinNum == 1) return &nor1;
	else exit(-1);
}

DCSComponent* DCSSRLatch::getRightComponent(int &inPinNum) {
	if (inPinNum == 0) return &nor0;
	else if (inPinNum == 1) return &nor1;
	else exit(-1);
}

void DCSSRLatch::updateOut() {
	out[0] = nor0.getOutVal(0);
	out[1] = nor1.getOutVal(0);
	if (out[0] && out[1])
		throw "Illegal state";
}

