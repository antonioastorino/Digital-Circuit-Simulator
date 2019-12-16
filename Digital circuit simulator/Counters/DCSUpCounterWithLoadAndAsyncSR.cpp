//
//  DCSUpCounterWithLoadAndAsyncSR.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSUpCounterWithLoadAndAsyncSR::DCSUpCounterWithLoadAndAsyncSR(std::string name,
															   ushort numOfElements):
DCSComponent(name, false),
dividerArray(name + "-divArray", numOfElements),
nodeArray({
	name +"-Load",
	name +"-Clock",
	name +"-Clear",
	name +"-Preset"},
	4),
numOfElements(numOfElements)
{
	for (ushort i = 0; i < numOfElements; i ++) {
		for (ushort j = 0; j < 4; j ++) {
			/*
			 connect nodes to internal inputs of dividers:
			 1 = Load
			 2 = Clock
			 3 = Clear
			 4 = Preset
			 Node that inputs 0 and 5 of dividers are not shared
			 */
			nodeArray[j]->connect(dividerArray[i], 0, j + 1);
		}
	}
	for (ushort i = 0; i < numOfElements - 1; i++) {
		// cascade dividers
		dividerArray[i]->connect(dividerArray[i+1],
								 2, // Count out
								 5 // Count in
								 );
	}
	// NOTE: The first Count in is an array input.
	//       The last Count out is an array output.
	 
}
DCSComponent* DCSUpCounterWithLoadAndAsyncSR::getOutComponent(ushort &outPinNum) {
	if (outPinNum >=0 && outPinNum < numOfElements) {
		ushort arrayElement = outPinNum;
		outPinNum  = 0;
		return dividerArray[arrayElement]->getOutComponent(outPinNum);
	}
	else if (outPinNum == numOfElements) {
		outPinNum = 2;
		return dividerArray[numOfElements - 1]->getOutComponent(outPinNum);
	}
	else exit(-1);
}
DCSComponent* DCSUpCounterWithLoadAndAsyncSR::getInComponent(ushort &inPinNum) {
	if (inPinNum == 0) {
		inPinNum = 5;
		return dividerArray[0]->getInComponent(inPinNum); // Count in
	}
	else if (inPinNum < 5) {
		ushort arrayElement = inPinNum - 1;
		inPinNum = 0;
		return nodeArray[arrayElement];
	}
	else if (inPinNum < 5 + numOfElements) {
		ushort arrayElement = inPinNum - 5;
		inPinNum = 0; // Data
		return dividerArray[arrayElement]->getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

void DCSUpCounterWithLoadAndAsyncSR::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
