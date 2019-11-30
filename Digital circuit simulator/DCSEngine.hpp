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

#include "DCSIO.hpp"

class DCSEngine {
private:
	static std::vector<DCSComponent*> componentVector;
	static std::vector<DCSComponent*> inputVector;
	static int clockPeriod;
	static void printProbes();
	static void printLogicLevels();
public:
	static void addComponent(DCSComponent* component);
	static void addInput(DCSIO* input);
	static void run(int steps=10);
	static void initialize(std::vector<DCSComponent*> cVec = componentVector);
	static int getClockPeriod();
	static void setClockPeriod(int numberOfTimeDelays);
};

#endif /* DCSEngine_hpp */
