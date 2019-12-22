//
//  DCSRippleAdder8Bits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 21/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSRippleAdder8Bits::DCSRippleAdder8Bits(std::string name) :
DCSComponent(name, false),
faArray("FA", 8) {
	for (ushort i = 1; i < 8; i++) {
		faArray[i-1]->connect(faArray[i], 1, 2);
	}
}

DCSComponent* DCSRippleAdder8Bits::getInComponent(ushort &inPinNum) {
	ushort elementNumber;
	if (inPinNum < 8) {
		elementNumber = inPinNum;
		inPinNum = 0;
		return faArray[elementNumber]->getInComponent(inPinNum);
	}
	else if (inPinNum < 16) {
		elementNumber = inPinNum - 8;
		inPinNum = 1;
		return faArray[elementNumber]->getInComponent(inPinNum);
	}
	if (inPinNum == 16) {
		inPinNum = 2;
		return faArray[0]->getInComponent(inPinNum);
	}
	DCSLog::error(name, "Input pin number out of range");
	exit(-1);
}

DCSComponent* DCSRippleAdder8Bits::getOutComponent(ushort &outPinNum) {
	if (outPinNum < 8) {
		ushort elementNumber = outPinNum;
		outPinNum = 0;
		return faArray[elementNumber]->getOutComponent(outPinNum);
	}
	if (outPinNum == 8) {
		outPinNum = 1;
		return faArray[7]->getOutComponent(outPinNum);
	}
	DCSLog::error(name, "Output pin number out of range");
	exit(-1);
}

void DCSRippleAdder8Bits::updateOut() {
	throw "This function should never be called";
}

