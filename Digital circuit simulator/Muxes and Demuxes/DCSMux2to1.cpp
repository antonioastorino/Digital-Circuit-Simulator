//
//  DCSMux2to1.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 20/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 PINOUT:
 Input 0 - Data in 0
 Input 1 - Data in 1
 Input 2 - Selector
 
 Out 0 - Data out 0
 */

#include "DCSHeader.h"

DCSMux2to1::DCSMux2to1(std::string name) :
DCSComponent(name, false),
and0(name + "-And0"),
and1(name + "-And1"),
not0(name + "-Not0"),
del0(name + "-Del0"),
or0(name + "-Or0"),
node0(name + "-Sel0") {
	// Selector
	node0.connect(&not0, 0, 0);
	node0.connect(&del0, 0, 0);
	not0.connect(&and0, 0, 1);
	del0.connect(&and1, 0, 1);
	and0.connect(&or0, 0, 0);
	and1.connect(&or0, 0, 1);
	
	timeDelay = 2;
	numOfInPins = 3;
	numOfOutPins = 1;
}

DCSComponent* DCSMux2to1::getOutComponent(ushort &outPinNum) {
	if (outPinNum == 0) return &or0;
	DCSLog::error(name, "Output pin out of range");
	exit(-1);
}

DCSComponent* DCSMux2to1::getInComponent(ushort &inPinNum) {
	if (inPinNum == 0) return &and0;
	else if (inPinNum == 1) {
		inPinNum = 0;
		return &and1;
	}
	else if (inPinNum == 2) {
		inPinNum = 0;
		return &node0;
	}
	DCSLog::error(name, "Input pin out of range");
	exit(-1);
}

void DCSMux2to1::updateOut() {
	throw "This function should never be called";
}
