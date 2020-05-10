#ifndef DCSEngine_hpp
#define DCSEngine_hpp
#include "DCSDisplayNBits.hpp"
#include "DCSLog.hpp"

class DCSComponent;
class DCSInput;
class DCSWire;
class DCSRam16x8;

/**
 * @class DCSEngine
 * Static class providing all the functionalities needed to manage the system initialization and evolution.
 * 
 */
class DCSEngine {
private:
	static std::vector<DCSComponent*> componentVector;
	static std::vector<DCSComponent*> inputVector;
	static std::vector<DCSWire*> wireVector;
	static std::vector<DCSDisplayNBits*> displayVector;
	
	static uint16_t clockPeriod;
	static uint16_t stepNumber;
	static bool sampling;
	
	static void initCircuit(std::vector<DCSComponent*> cVec = inputVector);
	
	static void checkConnections();
	static void checkInitialization();
	
	static void updateComponents();
	static void updateInputs();
	static void propagateValues();
	static void printProbes();
	static void printLogicLevels();
	
public:
	static void initialize(uint16_t clockHalfPeriod);
	static void addComponent(DCSComponent* component);
	static void addInput(DCSInput* input);
	static void addWire(DCSWire* p_wire);
	static void addDisplay(DCSDisplayNBits* p_display);
	static void run(uint64_t steps=10, bool sampling=false, bool printOut=true);
	static int getClockPeriod();
	static int getStepNumber();
	static void setSampling(bool sampling);
	static void setHalfClockPeriod(uint16_t numberOfTimeSteps);
	static void restart();
	static void programMemory(DCSRam16x8 * memory, uint16_t program[16][2], bool printOut=true);
};

#endif /* DCSEngine_hpp */
