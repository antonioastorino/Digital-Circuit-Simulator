//
//  DCSDFlipFlop.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSDFlipFlop.hpp"

DCSDFlipFlop::DCSDFlipFlop(std::string name) :
DCSComponent(name, 2, 2, false) {
	node0.connect(&not0, 0, 0);
	node0.connect(&and0, 0, 0);
	not0.connect(&del0, 0, 0);
	del0.connect(&and0, 0, 1);
	and0.connect(&dLat0, 0, 1);
	dLat0.setParent(this);
}

DCSComponent* DCSDFlipFlop::getOutComponent(int &outPinNum) {
	return dLat0.getOutComponent(outPinNum);
}

DCSComponent* DCSDFlipFlop::getInComponent(int &inPinNum) {
	if (inPinNum == 0) return dLat0.getInComponent(inPinNum);
	else if (inPinNum == 1) {
		// input pin 1 is the clock, connected to the node pin 0
		inPinNum = 0;
		return &node0;
	}
	else exit(-1);
}

void DCSDFlipFlop::updateOut() {
	out = dLat0.getOutVec();
	updateParentOut();
}
