//
//  DCSComponent.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSComponent.hpp"
#include "DCSEngine.hpp"

DCSComponent::DCSComponent(std::string name, int fanIn, int fanOut, bool add):
enabled(true),		// only 3-state buffer can be disabled
name{name},
fanIn(fanIn),
fanOut(fanOut),
reachableIn(0),
allInReached((1 << fanIn) - 1), // 2^fanIn - 1
connectedIn(0),
fromTristateIn(0),
isNode(false),
isTristate(false) {
	if (add) DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
	for (auto wire: wireVector) {
		delete wire;
	}
}

// set single input
void DCSComponent::setIn(bool inVal, int inPinNum) {
	if (inPinNum >= fanIn) throw "Input pin number out of range";
	reachableIn |= 1 << inPinNum;
	in &= (~(1 << inPinNum)); // reset inPinNum-th bit
	in |= (inVal << inPinNum); // set the same bit to inVal
}

// set entire input array
void DCSComponent::setIn(uint64_t inVec) {
	in = inVec;
	reachableIn = allInReached;
	initialized = true;
}

// get single output
bool DCSComponent::getOutVal(int outPinNum) {
	if (reachableIn == allInReached) initialized = true;
	return (out >> outPinNum) & 1;
}


// get entire input array
uint64_t DCSComponent::getOutVec() {
	if (reachableIn == allInReached) initialized = true;
	return out;
}

void DCSComponent::connect(DCSComponent* to,
						   int outPinNum,
						   int inPinNum,
						   std::string probeName) {

	DCSComponent* leftComponent = getOutComponent(outPinNum);
	DCSComponent* rightComponent = to->getInComponent(inPinNum);
	
	if (leftComponent->isTristate) {
		rightComponent->setFromTristateIn(inPinNum);
	}
	else {
		rightComponent->setConnectedIn(inPinNum);
	}
	
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

std::string DCSComponent::getName() { return name; }

DCSComponent* DCSComponent::getInComponent(int &inPinNum) {
	return this;
}

DCSComponent* DCSComponent::getOutComponent(int &outPinNum) {
	return this;
}

bool DCSComponent::getConnectedIn(int inPinNum) {
	return connectedIn & (1 << inPinNum);
}

bool DCSComponent::getFromTristateIn(int inPinNum) {
	return fromTristateIn & (1 << inPinNum);
}

void DCSComponent::setConnectedIn(int inPinNum) {
	if (getConnectedIn(inPinNum) || getFromTristateIn(inPinNum)) {
		DCSLog::error(name, "trying to connect tristate output to connected input");
	}
	connectedIn |= (1 << inPinNum);
}

void DCSComponent::setFromTristateIn(int inPinNum) {
	if (getConnectedIn(inPinNum)) {
		DCSLog::error(name, "trying to connect tristate output to connected input");
	}
	fromTristateIn |= (1 << inPinNum);
}

void DCSComponent::propagateValues() {
	for (auto wire: wireVector) {
		wire->propagateValue();
	}
}

bool DCSComponent::isFullyConnected() {
	return (connectedIn ^ fromTristateIn) == allInReached;
}

/* Setting the parent ensures that the parent's output is updated every
 time the child's output changes
 */
void DCSComponent::setParent(DCSComponent* parent) {
	this->parent = parent;
}

void DCSComponent::updateParentOut() {
	if (parent != nullptr) parent->updateOut();
}

void DCSComponent::enable(){
	throw "Only 3-state buffers can access this function";
}

void DCSComponent::disable(){
	throw "Only 3-state buffers can access this function";
}

bool DCSComponent::getEnabled(){
	return enabled;
}
