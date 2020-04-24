//
//  DCSEngine.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSEngine_hpp
#define DCSEngine_hpp
#include "DCSDisplayNBits.hpp"
#include "DCSLog.hpp"

class DCSComponent;
class DCSInput;
class DCSWire;

class DCSEngine {
private:
	static std::vector<DCSComponent*> componentVector;
	static std::vector<DCSComponent*> inputVector;
	static std::vector<DCSWire*> wireVector;
	static std::vector<DCSDisplayNBits*> displayVector;
	
	static ushort clockPeriod;
	static ushort stepNumber;
	static bool sampling;
	
	static void initialize(std::vector<DCSComponent*> cVec = inputVector);
	
	static void checkConnections();
	static void checkInitialization();
	
	static void updateOutputs();
	static void propagateValues();
	
	static void printProbes();
	static void printLogicLevels();
	
	friend class DCSMemoryProgrammer;
public:
	static void reset(ushort clockHalfPeriod=5);
	static void addComponent(DCSComponent* component);
	static void addInput(DCSInput* input);
	static void addWire(DCSWire* p_wire);
	static void addDisplay(DCSDisplayNBits* p_display);
	static void run(uint64_t steps=10, bool sampling=false);
	static int getClockPeriod();
	static int getStepNumber();
	static void setSampling(bool sampling);
	static void setHalfClockPeriod(ushort numberOfTimeSteps);
};

#endif /* DCSEngine_hpp */
