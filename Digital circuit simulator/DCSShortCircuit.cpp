//
//  DCSShortCircuit.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSShortCircuit.hpp"

DCSShortCiruit::DCSShortCiruit() :
DCSComponent(1,1,false) {
	
}

void DCSShortCiruit::updateOut() {
	// nothing to do because the output is updated when the input changes
}

void DCSShortCiruit::setIn(bool inVal, int inPinNum) {
	in &= (~(1 << inPinNum)); // reset inPinNum-th bit
	in |= (inVal << inPinNum); // set the same bit to inVal
	out = in;
	for (auto wire_p: wireVector) {
		wire_p->propagateValue();
	}
}

void DCSShortCiruit::setIn(uint64_t inVec) {
	in = inVec;
	out = inVec;
	for (auto wire_p: wireVector) {
		wire_p->propagateValue();
	}
}
