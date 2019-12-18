//
//  DCSAddressDecoder4Bits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSAddressDecoder4Bits::DCSAddressDecoder4Bits(std::string name) :
DCSComponent(name, false),
nodeArray(name + "-In", 4),
notArray(name + "-Not", 4),
delArray(name + "-Del", 4),
and4Array(name + "-And4", 16){
	for (ushort i = 0; i < 4; i++) {
		nodeArray[i]->connect(delArray[i], 0, 0);
		nodeArray[i]->connect(notArray[i], 0, 0);
		for (ushort IN = 0; IN < 16; IN ++) {
			if ((IN >> i) & 1) {
				delArray[i]->connect(and4Array[IN], 0, i);
			}
			else {
				notArray[i]->connect(and4Array[IN], 0, i);
			}
		}
	}
}

DCSComponent* DCSAddressDecoder4Bits::getOutComponent(ushort &outPinNum) {
	if (outPinNum < 16) {
		ushort elementNumber = outPinNum;
		outPinNum = 0;
		return and4Array[elementNumber]->getOutComponent(outPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

DCSComponent* DCSAddressDecoder4Bits::getInComponent(ushort &inPinNum) {
	if (inPinNum < 4) {
		ushort elementNumber = inPinNum;
		inPinNum = 0;
		return nodeArray[elementNumber]->getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

void DCSAddressDecoder4Bits::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
