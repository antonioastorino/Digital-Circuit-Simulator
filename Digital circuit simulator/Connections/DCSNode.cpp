//
//  DCSNode.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Input 0 (data) needs to be ready at least 1 td before input 1 is asserted.
 Input 1 and 0 must be stable at least 2 td.
 The output is stable after 4 td from the change in the input
 Here is an example:
	   |  ____
 DATA: | X    XXXXXXX
       |  <--> 4 td
	   |   ___
 EN:   | __   _______
       |
       |      _______
 OUT:  | XXXXX
 
 */

#include "DCSNode.hpp"

DCSNode::DCSNode(std::string name) :
DCSComponent(name, 1, 1, false) {
	isNode = true;
	allInReached = -1; // ensures that nodes are never skipped during engine initialization
}

void DCSNode::updateOut() {
	// nothing to do because the output is updated when the input changes
}

void DCSNode::setIn(bool inVal, int inPinNum) {
	DCSComponent::setIn(inVal, inPinNum);

	out = in;
	for (auto wire_p: wireVector) {
		wire_p->propagateValue();
	}
}

void DCSNode::setIn(uint64_t inVec) {
	in = inVec;
	out = inVec;
	for (auto wire_p: wireVector) {
		wire_p->propagateValue();
	}
}


