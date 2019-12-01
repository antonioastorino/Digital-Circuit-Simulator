//
//  DCSComponent.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSComponent.hpp"
#include "DCSEngine.hpp"

DCSComponent::DCSComponent(int fanIn, int fanOut, bool add):
fanIn(fanIn),
fanOut(fanOut),
reachableIn(0),
allInReached((1 << fanIn) - 1) {
	in = new bool[fanIn];
	out = new bool[fanOut];
	if (add) DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
	delete [] in;
	delete [] out;
	for (auto wire: wireVector) {
		delete wire;
	}
}

// set single input
void DCSComponent::setIn(bool inVal, int inPinNum) {
	reachableIn |= 1 << inPinNum;
	in[inPinNum] = inVal;
}

// get single output
bool DCSComponent::getOutVal(int outPinNum) {
	if (reachableIn == allInReached) initialized = true;
	return out[outPinNum];
}

// set entire input array
void DCSComponent::setIn(bool* inVec) {
	for (int i = 0; i < fanIn; i++) {
		in[i] = inVec[i];
	}
	initialized = true;
}

// get entire input array
bool* DCSComponent::getOutVec() {
	if (reachableIn == allInReached) initialized = true;
	return out;
}

void DCSComponent::connect(DCSComponent* to,
						   int outPinNum,
						   int inPinNum,
						   std::string probeName) {

	DCSComponent* leftComponent = getLeftComponent(outPinNum);
	DCSComponent* rightComponent = to->getRightComponent(inPinNum);
	
	bool addToTheRight = true;
	for (auto component: leftComponent->rightComponentVector) {
		if (rightComponent == component) {
			addToTheRight = false;
			break;
		}
	}
	if (addToTheRight) leftComponent->rightComponentVector.push_back(rightComponent);
	
	
	DCSWire* wire = new DCSWire(leftComponent,
						   outPinNum,
						   rightComponent,
						   inPinNum,
						   probeName);
	
	wireVector.push_back(wire);
	DCSEngine::addWire(wire);
}

DCSComponent* DCSComponent::getRightComponent(int &inPinNum) {
	return this;
}

DCSComponent* DCSComponent::getLeftComponent(int outPinNum) {
	return this;
}

void DCSComponent::propagateValues() {
	for (auto wire: wireVector) {
		wire->propagateValue();
	}
}

void DCSComponent::setParent(DCSComponent* parent) {
	this->parent = parent;
}

void DCSComponent::updateParentOut() {
	if (parent != nullptr) parent->updateOut();
}
