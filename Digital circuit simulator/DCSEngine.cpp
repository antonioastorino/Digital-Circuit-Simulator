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
std::vector<DCSDisplayNBits*> DCSEngine::displayVector = {};

ushort DCSEngine::clockPeriod;
ushort DCSEngine::stepNumber;
bool DCSEngine::sampling;

void DCSEngine::reset(ushort clockHalfPeriod) {
	componentVector = {};
	inputVector = {};
	wireVector = {};
	displayVector = {};
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

void DCSEngine::addDisplay(DCSDisplayNBits* p_display) {
	displayVector.push_back(p_display);
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
	stepNumber = 0;
	/* Check if all components are connected */
	checkConnections();
	initialize();
	printLogicLevels();
	checkInitialization();
	
	for (stepNumber = 1; stepNumber <= steps; stepNumber++) {
		updateOutputs();
		propagateValues();
#if LOG_LEVEL>0
		printLogicLevels();
#endif
	}
}

void DCSEngine::checkConnections() {
	for (auto component: componentVector) {
		if(!(component->isFullyConnected())) {
			DCSLog::error(component->getName(), "not connected");
		}
	}
}

void DCSEngine::checkInitialization() {
	for (auto component: componentVector) {
		if (!(component->initialized)) {
			DCSLog::debug(component->getName(), "not initialized");
		}
	}
}

void DCSEngine::updateOutputs() {
	for (auto input: inputVector) { input->updateOut(); }
	for (auto component: componentVector) { component->updateOut(); }
}

void DCSEngine::propagateValues() {
	// assing the output value of a given pin to the connected input pin
	for (auto wire: wireVector) {
		wire->propagateValue();
	}
}

void DCSEngine::printLogicLevels() {
	if (!sampling || DCSEngine::stepNumber % (clockPeriod/2) == 1) {
		for (auto wire: wireVector) {
			if (wire->getProbeName().length() > 0) {
				std::string message;
				if (wire->getOutVal()) message = "1";
				else message = "0";
				DCSLog::output(wire->getProbeName(), message);
			}
		}
		for (auto display: displayVector) { display->updateOut(); }
		std::stringstream n; n << stepNumber -1 << '\n';
		DCSLog::output("STEP", n.str());
	}
}

int DCSEngine::getClockPeriod() { return clockPeriod; };
int DCSEngine::getStepNumber() { return stepNumber; }
void DCSEngine::setSampling(bool sampling) { DCSEngine::sampling = sampling; }
void DCSEngine::setHalfClockPeriod(ushort numberOfTimeSteps) {
	clockPeriod = 2 *numberOfTimeSteps;
};

