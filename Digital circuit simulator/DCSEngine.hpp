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

class DCSComponent;
class DCSInput;
class DCSWire;

class DCSEngine {
private:
	static std::vector<DCSComponent*> componentVector;
	static std::vector<DCSComponent*> inputVector;
	static std::vector<DCSWire*> wireVector;
	
	static ushort clockPeriod;
	static ushort stepNumber;
	static bool sampling;
	
	static void printProbes();
	static void printLogicLevels();
	static void propagateValues();
public:
	static void reset(ushort clockHalfPeriod=5, bool sampling=false);
	static void addComponent(DCSComponent* component);
	static void addInput(DCSInput* input);
	static void addWire(DCSWire* p_wire);
	static void run(uint64_t steps=10);
	static void initialize(std::vector<DCSComponent*> cVec = inputVector);
	static int getClockPeriod();
	static int getStepNumber();
	static void setSampling(bool sampling);
	static void setHalfClockPeriod(ushort numberOfTimeSteps);
};

#endif /* DCSEngine_hpp */
