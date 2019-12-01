//
//  DCSInput.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSInput.hpp"
#include "DCSEngine.hpp"

DCSInput::DCSInput(bool constValue) :
DCSComponent(0, 1, false),
signal({0}),
constValue(constValue){
	DCSEngine::addInput(this);
}

DCSInput::DCSInput(binary_signal signal) :
DCSComponent(1, 1, false),
signal(signal),
constValue(0) {
	hasSignal = true;
	DCSEngine::addInput(this);
}

void DCSInput::updateOut() {
	if (hasSignal) out[0] = signal.getVal(DCSEngine::getStepNumber());
	else out[0] = constValue;
}
