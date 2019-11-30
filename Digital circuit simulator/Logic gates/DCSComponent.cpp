//
//  DCSComponent.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSComponent.hpp"
#include "DCSEngine.hpp"

DCSComponent::DCSComponent(int fanIn, int fanOut, bool add): fanIn(fanIn), fanOut(fanOut) {
	in = new bool[fanIn];
	out = new bool[fanOut];
	if (add) DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
	delete [] in;
	delete [] out;
}

// set single input
void DCSComponent::setIn(bool inVal, int inPinNum) {
	in[inPinNum] = inVal;
};

// get single output
bool DCSComponent::getOutVal(int outPinNum) {
	return out[outPinNum];
}

// set entire input array
void DCSComponent::setIn(bool* inVec) {
	for (int i = 0; i < fanIn; i++) {
		in[i] = inVec[i];
	}
}

// get entire input array
bool* DCSComponent::getOutVal() {
	return out;
}

void DCSComponent::connect(DCSComponent* to,
						   int outPinNum,
						   int inPinNum,
						   std::string probeName) {
	connectedComponentVector.push_back(to);
	wireVector.push_back(DCSWire(this,
								 outPinNum,
								 to,
								 inPinNum,
								 probeName));
}

std::vector<DCSComponent*> DCSComponent::getConnectedComponentVector() {
	return connectedComponentVector;
}

void DCSComponent::propagateValue() {
	// assing the output value of a given pin to the connected input pin
	for (auto wire: wireVector) {
		wire.to->setIn(out[wire.outPinNum], in[wire.inPinNum]);
	}
}
