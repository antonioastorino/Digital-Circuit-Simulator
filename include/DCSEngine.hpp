#ifndef DCSEngine_hpp
#define DCSEngine_hpp
#include "DCSDisplayNBits.hpp"
#include "DCSLog.hpp"

class DCSComponent;
class DCSInput;
class DCSWire;
class DCSRam16x8;
class DCSRam256x16;

/**
 * @class DCSEngine
 * Static class providing all the functionalities needed to manage the system initialization and
 * evolution.
 *
 */
class DCSEngine {
private:
    static std::vector<DCSComponent*> ramComponentVector; // temporarily stores components of a RAM
    static std::vector<DCSWire*> ramWireVector;           // temporarily stores wires of a RAM
    static std::vector<DCSComponent*> componentVector;
    static std::vector<DCSComponent*> inputVector;
    static std::vector<DCSWire*> wireVector;
    static std::vector<DCSDisplayNBits*> displayVector;

    static uint16_t clockPeriod;
    static uint16_t stepNumber;
    static bool sampling;
    static bool ramReady;// makes sure ram are activated after being programmed and before being connected to the circuit

    static void storeRamElements();
    static void resetAndKeepRamElements();

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
    static void run(uint64_t steps = 10, bool sampling = false, bool printOut = true);
    static int getClockPeriod();
    static int getStepNumber();
    static void setSampling(bool sampling);
    static void setHalfClockPeriod(uint16_t numberOfTimeSteps);
    static void restart();
    static void programMemory(DCSRam16x8* memory, uint16_t program[16][2], bool printOut = true);
    static void programControlUnit(DCSRam256x16* memory, bool printOut = true);
    static void useRamElements();
};

#endif /* DCSEngine_hpp */
