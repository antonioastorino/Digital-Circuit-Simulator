//
//  DCSEngine.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSEngine.hpp"
#include <iostream>

std::vector<DCSComponent*> DCSEngine::componentVector = {};
std::vector<DCSComponent*> DCSEngine::inputVector = {};
int DCSEngine::clockPeriod = 10;
int DCSEngine::stepNumber = 0;

void DCSEngine::addComponent(DCSComponent* component) {
	componentVector.push_back(component);
}

void DCSEngine::addInput(DCSIO* input) {
	inputVector.push_back(input);
}

void DCSEngine::initialize(std::vector<DCSComponent*> cVec) {
	std::vector<DCSComponent*> leftComponent = {};
	for (auto component: cVec) {
		if (!(component->initialized)){
			component->initialized = true;
			component->updateOut();
			component->propagateValue();
			for (auto wire: component->wireVector) {
				leftComponent.push_back(wire.to);
			}
			initialize(leftComponent);
		}
	}
}

void DCSEngine::run(int steps) {

	// update output values of initial layer (input vector)
	DCSEngine::printProbes();
	for (int i = 0; i < steps; i++) {
		stepNumber = i;
		
		for (auto component: componentVector) {
			component->updateOut();
		}
		// Update input of components connected to other components
		for (auto component: componentVector) {
			component->propagateValue();
		}

		DCSEngine::printLogicLevels();
	}
}

void DCSEngine::printProbes() {
	for (auto component: componentVector) {
		for (auto wire: component->wireVector) {
			if (wire.probeName.length() > 0) {
				std::cout << wire.probeName << " ";
			}
		}
	}
	std::cout << std::endl;
}

void DCSEngine::printLogicLevels() {
	for (auto component: componentVector) {
		for (auto wire: component->wireVector) {
			if (wire.probeName.length() > 0) {
				for (int i = 0; i < wire.probeName.length()-1; i++) {
					std::cout << ' ';
				}
				std::cout << component->getOutVal()[wire.getOutPinNum()] << " ";
			}
		}
	}
	std::cout << std::endl;
}

int DCSEngine::getClockPeriod() { return clockPeriod; };
int DCSEngine::getStepNumber() { return stepNumber; }

void DCSEngine::setClockPeriod(int numberOfTimeDelays) {
	clockPeriod = numberOfTimeDelays;
};
