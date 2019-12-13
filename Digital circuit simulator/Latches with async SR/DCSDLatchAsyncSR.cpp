//
//  DCSDLatchAsyncSR.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSDLatchAsyncSR::DCSDLatchAsyncSR(std::string name) :
DCSComponent(name, false) {
	node0.connect(&and1, 0, 1);
	node0.connect(&not0, 0, 0);
	node1.connect(&and0, 0, 1);
	node1.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 0);
	and0.connect(&nor3_0, 0, 0);
	and1.connect(&nor3_1, 0, 1);
	nor3_0.connect(&nor3_1, 0, 0);
	nor3_1.connect(&nor3_0, 0, 1);
}

DCSComponent* DCSDLatchAsyncSR::getOutComponent(ushort &outPinNum) {
	if (outPinNum == 0) return &nor3_0;
	else if (outPinNum == 1) {
		outPinNum = 0;
		return &nor3_1;
	}
	else exit(-1);
}

DCSComponent* DCSDLatchAsyncSR::getInComponent(ushort &inPinNum) {
	switch (inPinNum) {
		case 0:
			return &node0;
			break;
		case 1:
			inPinNum = 0;
			return &node1;
			break;
		case 2:
			return &nor3_0;
			break;
		case 3:
			inPinNum = 2;
			return &nor3_1;
			break;
		default:
			exit(-1);
			break;
	}
}

void DCSDLatchAsyncSR::updateOut() {
	throw "This function should never be called";
}
