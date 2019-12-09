//
//  DCSEngine.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSEngine_hpp
#define DCSEngine_hpp

#include <vector>
#include "DCSComponent.hpp"
#include "DCSWire.hpp"
#include "DCSInput.hpp"

class DCSEngine {
private:
	static std::vector<DCSComponent*> componentVector;
	static std::vector<DCSComponent*> inputVector;
	static std::vector<DCSWire*> wireVector;
	static int clockPeriod;
	static int stepNumber;
	static void printProbes();
	static void printLogicLevels();
	static void propagateValues();
public:
	static void addComponent(DCSComponent* component);
	static void addInput(DCSInput* input);
	static void addWire(DCSWire* p_wire);
	static void run(int steps=10);
	static void initialize(std::vector<DCSComponent*> cVec = inputVector);
	static int getClockPeriod();
	static int getStepNumber();
	static void setClockPeriod(int numberOfTimeDelays);
};

#endif /* DCSEngine_hpp */
