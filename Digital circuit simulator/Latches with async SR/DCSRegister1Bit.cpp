//
//  DCSRegister1Bit.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSRegister1Bit::DCSRegister1Bit(std::string name) :
DCSComponent(name, false) {
	node0.connect(&not0, 0, 0);
	node0.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 1);
	dffsr0.connect(&and0, 0, 0);
	and0.connect(&or0, 0, 0);
	and1.connect(&or0, 0, 1);
	or0.connect(&dffsr0, 0, 0);
}

DCSComponent* DCSRegister1Bit::getOutComponent(ushort &outPinNum) {
	return dffsr0.getOutComponent(outPinNum);
}
DCSComponent* DCSRegister1Bit::getInComponent(ushort &inPinNum) {
	switch (inPinNum) {
		case 0:
			inPinNum = 1;
			return &and1;
			break;
		case 1:
			return dffsr0.getInComponent(inPinNum);
			break;
		case 2:
			return dffsr0.getInComponent(inPinNum);
			break;
		case 3:
			return dffsr0.getInComponent(inPinNum);
			break;
		case 4:
			inPinNum = 0;
			return &node0;
			break;
		default:
			break;
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}
void DCSRegister1Bit::updateOut() {
	
}

