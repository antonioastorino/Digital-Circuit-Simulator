//
//  DCSSRLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSSRLatch::DCSSRLatch(std::string name) :
DCSComponent(name, false) {
	nor0.connect(&nor1, /*out*/ 0, /*in*/ 0);
	nor1.connect(&nor0, /*out*/ 0, /*in*/ 1);
}

DCSComponent* DCSSRLatch::getOutComponent(ushort &outPinNum) {
	if (outPinNum == 0) return &nor0;
	else if (outPinNum == 1) {
		outPinNum = 0;
		return &nor1;
	}
	else exit(-1);
}

DCSComponent* DCSSRLatch::getInComponent(ushort &inPinNum) {
	if (inPinNum == 0) return &nor0;
	else if (inPinNum == 1) return &nor1;
	else exit(-1);
}

void DCSSRLatch::updateOut() {
	throw "This function should never be called";
}

