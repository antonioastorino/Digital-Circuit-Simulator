#include "DCSEngine.hpp"
#include "DCSArbitrarySignal.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSWire.hpp"
#include "DCSTimer.hpp"
#include <thread>

std::vector<DCSComponent*> DCSEngine::componentVector  = {};
std::vector<DCSComponent*> DCSEngine::inputVector      = {};
std::vector<DCSWire*> DCSEngine::wireVector            = {};
std::vector<DCSDisplayNBits*> DCSEngine::displayVector = {};

uint16_t DCSEngine::clockPeriod;
uint16_t DCSEngine::stepNumber;
bool DCSEngine::sampling;

void DCSEngine::initialize(uint16_t clockHalfPeriod) {
    componentVector = {};
    inputVector     = {};
    wireVector      = {};
    displayVector   = {};
    clockPeriod     = 2 * clockHalfPeriod;
    stepNumber      = 0;
}

void DCSEngine::addComponent(DCSComponent* component) { componentVector.push_back(component); }
void DCSEngine::addInput(DCSInput* input) { inputVector.push_back(input); }
void DCSEngine::addWire(DCSWire* p_wire) { wireVector.push_back(p_wire); }
void DCSEngine::addDisplay(DCSDisplayNBits* p_display) { displayVector.push_back(p_display); }

void DCSEngine::run(uint64_t steps, bool sampling) {
    
    DCSTimer::initialize();

    DCSEngine::sampling   = sampling;
    DCSEngine::stepNumber = 0;

    // Check if all components are connected
    checkConnections();

    // Put the circuit in a plausible initial state
    {
        PROFILE_WITH_CUSTOM_NAME("initCircuit");
        initCircuit();
    }
    std::thread t1;

    // Check that all the components are initialized
    t1 = std::thread(checkInitialization);
    printLogicLevels();
    // Print the initial state -- step -1
    t1.join();

    for (stepNumber = 1; stepNumber <= steps; stepNumber++) {
        updateInputs();
        updateComponents();

        t1 = std::thread(propagateValues);

        printLogicLevels();

#if LOG_LEVEL > 0
        t1.join();
#endif
    }
}

void DCSEngine::checkConnections() {
    PROFILE();
    for (auto component : componentVector) {
        if (!(component->isFullyConnected())) {
            DCSLog::error(component->getName(), 1);
        }
        // initialize updateByVector with nullptr
        for (uint16_t i = 0; i < component->getNumOfInPins(); i++)
            component->updatedByVector.push_back(nullptr);
    }
    for (auto display : displayVector) {
        if (!(display->isFullyConnected())) {
            DCSLog::error(display->getName(), 1);
        }
        // initialize updateByVector with nullptr
        for (uint16_t i = 0; i < display->getNumOfInPins(); i++)
            display->updatedByVector.push_back(nullptr);
    }
}

void DCSEngine::initCircuit(std::vector<DCSComponent*> cVec) {
    /*
     This procedure propagates the first input value though the network.
     If there are no inputs connected (in case of free-running FSM)
     then `cVec` is empty. In this case, the algorithm uses all the components
     as starting propagation point using DSF.
     */
    if (cVec.size() == 0) {
        cVec = componentVector;
    }
    // Array of components from which to propagate at the next iteration
    std::vector<DCSComponent*> newComponentVector = {};
    for (auto component : cVec) {
        if (component->isNode() || (!(component->isInitialized()) && component->isEnabled())) {
            component->updateOut();
            if (component->isNode()) {
                newComponentVector = component->rightComponentVector;
                initCircuit(newComponentVector);
            } else if (component->propagateValues()) {
                newComponentVector = component->rightComponentVector;
                if (newComponentVector.size()) //
                    initCircuit(newComponentVector);
            }
        }
    }
}

void DCSEngine::checkInitialization() {
    PROFILE();
    for (auto component : DCSEngine::componentVector) {
        if (!(component->isInitialized())) {
            DCSLog::debug(component->getName(), "I'm not initialized");
        }
    }
}

void DCSEngine::updateInputs() {
    PROFILE();
    for (auto input : inputVector)
        input->updateOut();
}

void DCSEngine::updateComponents() {
    PROFILE();
    for (auto component : DCSEngine::componentVector) {
        if (!component->isNode())
            component->updateOut();
        component->resetUpdatedByVector();
    }
}

void DCSEngine::propagateValues() {
    PROFILE();
    // assing the output value of a given pin to the connected input pin
    for (auto wire : wireVector) {
        if (!wire->fromNode()) // Nodes propagate themselves when updated
            wire->propagateValue();
    }
}

void DCSEngine::printLogicLevels() {
    PROFILE();
    if (!sampling || DCSEngine::stepNumber % (clockPeriod / 2) == 1) {
        for (auto wire : wireVector) {
            if (wire->getProbeName().length() > 0) {
                std::string message;
                if (wire->getOutVal())
                    DCSLog::output(wire->getProbeName(), "1");
                else
                    DCSLog::output(wire->getProbeName(), "0");
            }
        }
        for (auto display : displayVector) {
            display->updateOut();
        }
        std::stringstream n;
        n << stepNumber - 1 << '\n';
        DCSLog::output("STEP", n.str());
    }
}

int DCSEngine::getClockPeriod() {
        return clockPeriod; };
int DCSEngine::getStepNumber() {
        return stepNumber; }
void DCSEngine::setSampling(bool sampling) {
        DCSEngine::sampling = sampling; }
void DCSEngine::setHalfClockPeriod(uint16_t numberOfTimeSteps) {
    clockPeriod = 2 * numberOfTimeSteps;
};
