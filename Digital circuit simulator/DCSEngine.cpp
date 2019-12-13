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
int DCSEngine::clockPeriod;
int DCSEngine::stepNumber;

void DCSEngine::reset() {
	componentVector = {};
	inputVector = {};
	wireVector = {};
	clockPeriod = 10;
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
// this procedure propagates the first input value though the network. If there are no inputs connected (in case of free-running FSM), then it propagates the default output of all the components. It implements the BFS
	if (cVec.size() == 0) { cVec = componentVector; }
	// Array of components from which to propagate at the next iteration
	std::vector<DCSComponent*> leftComponentVector = {};
	DCSLog::info("Engine", "layer ------------------");
	for (auto component: cVec) {
		if (!(component->initialized) && component->getEnabled()){
			component->updateOut();
			if (component->isNode) {
				leftComponentVector = component->rightComponentVector;
				initialize(leftComponentVector);
			}
			else if (component->propagateValues()) {
				leftComponentVector = component->rightComponentVector;
				initialize(leftComponentVector);
			}
		}
	}
}

void DCSEngine::run(int steps) {
	/* Check if all components are connected */
	for (auto component: componentVector) {
		if(!(component->isFullyConnected())) {
			DCSLog::error(component->getName(), "not connected");
		}
	}
	
	DCSLog::info("Engine", "\n--------------Initialization start--------------\n");
	DCSEngine::initialize();
	DCSLog::info("Engine", "\n---------------Initialization end---------------\n");
	
	for (auto component: componentVector) {
		if (!(component->initialized)) {
			std::cout << component->getName() << " not connected \n";
		}
	}
	// update output values of initial layer (input vector)
	DCSEngine::printProbes();
	for (int i = 1; i < steps; i++) {
		stepNumber = i;
		
		for (auto input: inputVector) {
			input->updateOut();
		}
		
		for (auto component: componentVector) {
			component->updateOut();
		}

		propagateValues();

		DCSEngine::printLogicLevels();
	}
}

void DCSEngine::propagateValues() {
	// assing the output value of a given pin to the connected input pin
	for (auto wire: wireVector) {
		wire->propagateValue();
	}
}

void DCSEngine::printProbes() {
	for (auto wire: wireVector) {
		if (wire->getProbeName().length() > 0) {
			std::cout << "  " << wire->getProbeName() << " ";
		}
	}
	std::cout << std::endl;
}

void DCSEngine::printLogicLevels() {
		for (auto wire: wireVector) {
			if (wire->getProbeName().length() > 0) {
				for (int i = 0; i < wire->getProbeName().length(); i++) {
					std::cout << ' ';
				}
				bool currVal = wire->getOutVal();
				if (currVal)
					std::cout << " 1 ";
				else std::cout << " 0 ";

			}
		}
	std::cout << std::endl;
}

int DCSEngine::getClockPeriod() { return clockPeriod; };
int DCSEngine::getStepNumber() { return stepNumber; }

void DCSEngine::setClockPeriod(int numberOfTimeDelays) {
	clockPeriod = numberOfTimeDelays;
};

