#include "DCSEngine.hpp"
#include "DCSArbitrarySignal.hpp"
#include "DCSComponentArray.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSTimer.hpp"
#include "DCSWire.hpp"
#include "DCSUnitDelay.hpp"

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
    {
        PROFILE_WITH_CUSTOM_NAME("initialize");

        DCSEngine::sampling   = sampling;
        DCSEngine::stepNumber = 0;

        // Check if all components are connected
        checkConnections();

        // Put the circuit in a plausible initial state
        initCircuit();
        // Check that all the components are initialized
        checkInitialization();
        // Print the initial state -- step -1
        printLogicLevels();
    }

    {
        PROFILE_WITH_CUSTOM_NAME("run loop");
        for (stepNumber = 1; stepNumber <= steps; stepNumber++) {
            updateInputs();
            updateComponents();
            propagateValues();
#if LOG_LEVEL > 0
            printLogicLevels();
#endif
        }
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
    for (auto component : DCSEngine::componentVector) {
        if (!(component->isInitialized())) {
            DCSLog::debug(component->getName(), "I'm not initialized");
        }
    }
}

void DCSEngine::updateInputs() {
    for (auto input : inputVector)
        input->updateOut();
}

void DCSEngine::updateComponents() {
    for (auto component : DCSEngine::componentVector) {
        if (!component->isNode())
            component->updateOut();
        component->resetUpdatedByVector();
    }
}

void DCSEngine::propagateValues() {
    // assing the output value of a given pin to the connected input pin
    for (auto wire : wireVector) {
        if (!wire->fromNode()) // Nodes propagate themselves when updated
            wire->propagateValue();
    }
}

void DCSEngine::printLogicLevels() {
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

int DCSEngine::getClockPeriod() { return clockPeriod; };
int DCSEngine::getStepNumber() { return stepNumber; }
void DCSEngine::setSampling(bool sampling) { DCSEngine::sampling = sampling; }
void DCSEngine::setHalfClockPeriod(uint16_t numberOfTimeSteps) {
    clockPeriod = 2 * numberOfTimeSteps;
};

void DCSEngine::programMemory(DCSRam16x8* memory, uint16_t program[16][2]) {

    // store the engine state
    static std::vector<DCSComponent*> componentVector_tmp(DCSEngine::componentVector.size());
    static std::vector<DCSComponent*> inputVector_tmp(DCSEngine::inputVector.size());
    static std::vector<DCSWire*> wireVector_tmp(DCSEngine::wireVector.size());
    static std::vector<DCSDisplayNBits*> displayVector_tmp(DCSEngine::displayVector.size());

    std::copy(componentVector.begin(), componentVector.end(), componentVector_tmp.begin());
    std::copy(inputVector.begin(), inputVector.end(), inputVector_tmp.begin());
    std::copy(wireVector.begin(), wireVector.end(), wireVector_tmp.begin());
    std::copy(displayVector.begin(), displayVector.end(), displayVector_tmp.begin());

    // ask the component to save its state too (wires and right component vector)

    // add the components necessary to create a program
    {
        PROFILE_WITH_CUSTOM_NAME("Ram programming");
        uint16_t hcp           = DCSEngine::clockPeriod;

        DCSComponentArray<DCSInput> inArray0("In", memory->getNumOfInPins());
        DCSComponentArray<DCSOutput> outArray0("Out", 5);

        DCSDisplayNBits dispAddr("ADDR", 4);
        DCSDisplayNBits dispData("DATA", 8);
        DCSDisplayNBits dispOut("OUT", 8);

        inArray0.connect(memory); // control bits
        inArray0.connect(&dispAddr, {13, 16}, {0, 3});
        inArray0.connect(&dispData, {5, 12}, {0, 7});
        inArray0.connect(&outArray0, {0, 4}, {0, 4}, {"OE", "CLK", "R", "S", "WR"});
        memory->connect(&dispOut);

        inArray0[0]->makeSignal(1); // Enable
        inArray0[1]->makeSquareWave(hcp / 2);
        inArray0[2]->makeSignal(std::string("1111000000")); // Clear - reset the ram before loading
        inArray0[3]->makeSignal(0);        // Preset
        inArray0[4]->makeSignal(1); // Write
        inArray0[13]->makeSquareWave(2 *hcp, false); // Addr 0
        inArray0[14]->makeSquareWave(4 * hcp, false); //  Addr 1
        inArray0[15]->makeSquareWave(8 * hcp, false); //  Addr 2
        inArray0[16]->makeSquareWave(16 * hcp, false); //  Addr 3

        std::stringstream s[8];
        for (int i =0; i < 16; i ++) {
            for (int j = 0; j < 4; j ++) { // 
                s[j] << (program[i][0] >> j & 1);
            }
            for (int j = 0; j < 4; j ++) {
                s[j + 4] << (program[i][1] >> j & 1);
            }
        }
        for (int i = 0; i < 8; i ++) {
            inArray0[5 + i]->makeSignal(s[i].str(), true);
        }
    // program memory
        DCSEngine::run(15 * hcp, true);

        memory->disconnect();
    }

    // restore the initial state
    // clear vectors
    componentVector.clear();
    inputVector.clear();
    wireVector.clear();
    displayVector.clear();

    // resize
    DCSEngine::componentVector.resize(componentVector_tmp.size());
    DCSEngine::inputVector.resize(inputVector_tmp.size());
    DCSEngine::wireVector.resize(wireVector_tmp.size());
    DCSEngine::displayVector.resize(displayVector_tmp.size());
    
    // restore values (the ram is safe)
    std::copy(componentVector_tmp.begin(), componentVector_tmp.end(), componentVector.begin());
    std::copy(inputVector_tmp.begin(), inputVector_tmp.end(), inputVector.begin());
    std::copy(wireVector_tmp.begin(), wireVector_tmp.end(), wireVector.begin());
    std::copy(displayVector_tmp.begin(), displayVector_tmp.end(), displayVector.begin());

}