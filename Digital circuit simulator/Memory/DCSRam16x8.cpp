//
//  DCSRam16x8.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSRam16x8::DCSRam16x8(std::string name) :
DCSComponent(name, false),
regArray(name + "-Reg8Arr0_", 16),
andArray0(name +"-ENAndArr0_", 16),
andArray1(name +"-WRAndArr1_", 16),
ctrlNodeArray({
	name +"-Enable",  // 0
	name +"-Clock",   // 1
	name +"-Clear",   // 2
	name +"-Preset",  // 3
	name +"-Write"},  // 4
			  5),
dataNodeArray(name +"-dataNodeArr0_", 8),
outNodeArray(name +"-outNodeArr0_", 8),
dec0(name + "-dec0") {
	for (ushort regNum = 0; regNum < 16; regNum ++) {
		// connect each decoder output pin to and gates at input 0
		// either for anding the Enable signal or the Write signal
		/* Enable */
		dec0.connect(andArray0[regNum], regNum, 0);
		ctrlNodeArray.connect(andArray0[regNum], 0, 1);
		andArray0.connect(regArray[regNum], regNum, 0);
		/* Write */
		dec0.connect(andArray1[regNum], regNum, 0);
		ctrlNodeArray.connect(andArray1[regNum], 4, 1);
		andArray1.connect(regArray[regNum], regNum, 4);
		// connect to register control pins

		ctrlNodeArray.connect(regArray[regNum], 1, 1); // Clock
		ctrlNodeArray.connect(regArray[regNum], 2, 2); // Clear
		ctrlNodeArray.connect(regArray[regNum], 3, 3); // Preset

		for (ushort j = 0; j < 8; j++) {
			// connect data in to all register data ins
			dataNodeArray.connect(regArray[regNum], j, 5+j); // Data
			// connect all register data outs to output nodes
		}
		regArray[regNum]->connect(&outNodeArray);
	}
}

DCSComponent* DCSRam16x8::getOutComponent(ushort &outPinNum) {
	if (outPinNum < 8) {
		return outNodeArray.getOutComponent(outPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

DCSComponent* DCSRam16x8::getInComponent(ushort &inPinNum) {
	if (inPinNum < 5) {
		return ctrlNodeArray.getInComponent(inPinNum);
	}
	else if (inPinNum < 13) {
		inPinNum -= 5;
		return dataNodeArray.getInComponent(inPinNum);
	}
	else if (inPinNum < 17) {
		inPinNum -= 13;
		return dec0.getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

void DCSRam16x8::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
