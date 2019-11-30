//
//  DCSSRLatch.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSSRLatch.hpp"
#include <iostream>

DCSSRLatch::DCSSRLatch() : DCSComponent(2, 2, false) {
	nor0.connect(&nor1, /*out*/ 0, /*in*/ 0, " Q");
	nor1.connect(&nor0, /*out*/ 0, /*in*/ 1, "!Q");
}

void DCSSRLatch::connect(DCSComponent* to,
						   int outPinNum,
						   int inPinNum,
						   std::string probeName) {
	
	DCSComponent* leftComponent;
	DCSComponent* rightComponent = to->internalComponetAtInput(inPinNum);
	
	if (outPinNum == 0) leftComponent = &nor0;
	else if (outPinNum == 1) leftComponent = &nor1;
	else exit(-1);
	
	wireVector.push_back(DCSWire(leftComponent,
								 0,
								 rightComponent,
								 inPinNum,
								 probeName));
}

DCSComponent* DCSSRLatch::internalComponetAtInput(int &inPinNum) {
	if (inPinNum == 0) {
		return &nor0;
	}
	else if (inPinNum == 1) {
		return &nor1;
	}
	else {
		exit(-1);
	}
}

void DCSSRLatch::updateOut() {
	
}

