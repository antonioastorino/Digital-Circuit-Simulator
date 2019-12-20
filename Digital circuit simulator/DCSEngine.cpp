//
//  DCSEngine.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

std::vector<DCSComponent*> DCSEngine::componentVector = {};
std::vector<DCSComponent*> DCSEngine::inputVector = {};
std::vector<DCSWire*> DCSEngine::wireVector = {};

ushort DCSEngine::clockPeriod;
ushort DCSEngine::stepNumber;
bool DCSEngine::sampling;

void DCSEngine::reset(ushort clockHalfPeriod) {
	componentVector = {};
	inputVector = {};
	wireVector = {};
	clockPeriod = 2 * clockHalfPeriod;
	stepNumber = 0;
}

void DCSEngine::addComponent(DCSComponent* component) {
	componentVector.push_back(component);
}

void DCSEngine::addInput(DCSInput* input) {
	inputVector.push_back(input);
}

void DCSEngine::addWire(DCSWire* p_wire) {
	wireVector.push_back(p_wire);
}

void DCSEngine::initialize(std::vector<DCSComponent*> cVec) {
	/*
	 This procedure propagates the first input value though the network.
	 If there are no inputs connected (in case of free-running FSM)
	 then `cVec` is empty. In this case, the algorithm uses all the components
	 as starting propagation point using DSF.
	 */
	if (cVec.size() == 0) { cVec = componentVector; }
	// Array of components from which to propagate at the next iteration
	std::vector<DCSComponent*> newComponentVector = {};
	for (auto component: cVec) {
		if (!(component->initialized) && component->getEnabled()){
			component->updateOut();
			if (component->isNode) {
				newComponentVector = component->rightComponentVector;
				initialize(newComponentVector);
			}
			else if (component->propagateValues()) {
				newComponentVector = component->rightComponentVector;
				if (newComponentVector.size()) //
					initialize(newComponentVector);
			}
		}
	}
}

void DCSEngine::run(uint64_t steps, bool sampling) {
	DCSEngine::sampling = sampling;
	/* Check if all components are connected */
	for (auto component: componentVector) {
		if(!(component->isFullyConnected())) {
			DCSLog::error(component->getName(), "not connected");
		}
	}
	
	DCSLog::debug("Engine", "--------------Initialization start--------------");
	initialize();
	DCSLog::debug("Engine", "---------------Initialization end---------------");
	
	for (auto component: componentVector) {
		if (!(component->initialized)) {
			DCSLog::debug(component->getName(), "not initialized");
		}
	}
	// update output values of initial layer (input vector)
	printProbes();
	for (int i = 1; i < steps; i++) {
		stepNumber = i;
		
		for (auto input: inputVector) { input->updateOut(); }
		for (auto component: componentVector) { component->updateOut(); }
		propagateValues();
		printLogicLevels();
	}
}

void DCSEngine::propagateValues() {
	// assing the output value of a given pin to the connected input pin
	for (auto wire: wireVector) {
		wire->propagateValue();
	}
}

void DCSEngine::printProbes() {
	std::stringstream s;
	for (auto wire: wireVector) {
		if (wire->getProbeName().length() > 0) {
			s << " " << wire->getProbeName();
		}
	}
	DCSLog::output(0, s.str());
}

void DCSEngine::printLogicLevels() {
	if (!sampling || DCSEngine::stepNumber % (clockPeriod/2) == 1) {
		std::stringstream s;
		for (auto wire: wireVector) {
			if (wire->getProbeName().length() > 0) {
				for (int i = 0; i < wire->getProbeName().length(); i++) {
					s << ' ';
				}
				bool currVal = wire->getOutVal();
				if (currVal)
					s << "1";
				else s << "0";
			}
		}
		DCSLog::output(stepNumber - 1, s.str());
	}
}

int DCSEngine::getClockPeriod() { return clockPeriod; };
int DCSEngine::getStepNumber() { return stepNumber; }
void DCSEngine::setSampling(bool sampling) { DCSEngine::sampling = sampling; }
void DCSEngine::setHalfClockPeriod(ushort numberOfTimeSteps) {
	clockPeriod = 2 *numberOfTimeSteps;
};

