//
//  DCSIO.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSIO.hpp"
#include "DCSEngine.hpp"

DCSIO::DCSIO(bool initValue) :
DCSComponent(1, 1),
signal({0}) {
	in[0] = initValue;
	DCSEngine::addInput(this);
}

DCSIO::DCSIO(binary_signal signal) :
DCSComponent(1, 1),
signal(signal) {
	initialized = true; // no need to initialized
	hasSignal = true;
	DCSEngine::addInput(this);
}

void DCSIO::updateOut() {
	if (hasSignal) out[0] = signal.getVal(DCSEngine::getStepNumber());
	else out[0] = in[0];
}
