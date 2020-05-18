#include "DCSEngine.hpp"
#include "DCSComponentArray.hpp"
#include "DCSInput.hpp"
#include "DCSInstructionSet.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSRam256x16.hpp"
#include "DCSTimer.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSWire.hpp"

std::vector<DCSComponent*> DCSEngine::ramComponentVector = {};
std::vector<DCSWire*> DCSEngine::ramWireVector           = {};
std::vector<DCSComponent*> DCSEngine::componentVector    = {};
std::vector<DCSComponent*> DCSEngine::inputVector        = {};
std::vector<DCSWire*> DCSEngine::wireVector              = {};
std::vector<DCSDisplayNBits*> DCSEngine::displayVector   = {};

uint64_t DCSEngine::clockPeriod;
uint64_t DCSEngine::s_stepNumber;
bool DCSEngine::sampling;
bool DCSEngine::ramReady;

void DCSEngine::initialize(uint64_t clockHalfPeriod) {
    ramComponentVector = {};
    ramWireVector      = {};
    componentVector    = {};
    inputVector        = {};
    wireVector         = {};
    displayVector      = {};
    clockPeriod        = static_cast<uint64_t>(2 * clockHalfPeriod);
    s_stepNumber       = static_cast<uint64_t>(0);
    ramReady           = true;
}

void DCSEngine::addComponent(DCSComponent* component) { componentVector.push_back(component); }
void DCSEngine::addInput(DCSInput* input) { inputVector.push_back(input); }
void DCSEngine::addWire(DCSWire* p_wire) { wireVector.push_back(p_wire); }
void DCSEngine::addDisplay(DCSDisplayNBits* p_display) { displayVector.push_back(p_display); }

void DCSEngine::storeRamElements() {
    // set ramReady to false to ensure useRamElements() is called
    ramReady = false;
    // extend the vector size
    size_t cSize  = componentVector.size();
    size_t wSize  = wireVector.size();
    size_t rCSize = ramComponentVector.size();
    size_t rWSize = ramWireVector.size();

    ramComponentVector.resize(rCSize + cSize);
    ramWireVector.resize(rWSize + wSize);
    // append the new elements
    std::copy(componentVector.begin(), componentVector.end(), ramComponentVector.begin() + rCSize);
    std::copy(wireVector.begin(), wireVector.end(), ramWireVector.begin() + rWSize);
}

void DCSEngine::resetAndKeepRamElements() {
    // clear vectors (restore the initial state)
    componentVector = {};
    inputVector     = {};
    wireVector      = {};
    displayVector   = {};
}

void DCSEngine::useRamElements() {
    ramReady = true;
    // extend the vector size
    size_t cSize  = componentVector.size();
    size_t wSize  = wireVector.size();
    size_t rCSize = ramComponentVector.size();
    size_t rWSize = ramWireVector.size();

    componentVector.resize(rCSize + cSize);
    wireVector.resize(rWSize + wSize);
    // append the new elements
    std::copy(ramComponentVector.begin(), ramComponentVector.end(),
              componentVector.begin() + cSize);
    std::copy(ramWireVector.begin(), ramWireVector.end(), wireVector.begin() + wSize);

    ramComponentVector = {};
    ramWireVector      = {};
}

void DCSEngine::run(uint64_t steps, bool sampling, bool printOut) {
    if (!ramReady)
        DCSLog::error("Engine", 17);

    DCSEngine::sampling     = sampling;
    DCSEngine::s_stepNumber = 0;
    {
        PROFILE_WITH_CUSTOM_NAME("Init circuit");

        // Check if all components are connected
        checkConnections();

        // Put the circuit in a plausible initial state
        initCircuit();
        // Check that all the components are initialized
        checkInitialization();
        // Print the initial state -- step -1
        if (printOut)
            printLogicLevels();


        ++s_stepNumber;
        updateInputs();
        updateComponents();
        propagateValues();
        if (printOut)
            printLogicLevels();

    }
    {
        PROFILE_WITH_CUSTOM_NAME("Run loop");
        for (++s_stepNumber; s_stepNumber <= steps; s_stepNumber++) {

            updateInputs();

            updateComponents();

            propagateValuesOnChangeOnly();

            if (printOut)
                printLogicLevels();
        }
    }
}

void DCSEngine::checkConnections() {
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
        // initialize updatedByVector with nullptr
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
        component->outChanged = true;
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

    for (auto display : DCSEngine::displayVector) {
        display->resetUpdatedByVector();
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

void DCSEngine::propagateValuesOnChangeOnly() {
    PROFILE();
    // assing the output value of a given pin to the connected input pin
    for (auto wire : wireVector) {
        if (!wire->fromNode())                  // Nodes propagate themselves when updated
            if (wire->from->needsPropagation()) // true if the output has changed during from the
                                                // previous time step
                wire->propagateValue();
    }
}

void DCSEngine::printLogicLevels() {
    if (!sampling || DCSEngine::s_stepNumber % (clockPeriod / 2) == 1) {
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
        if (s_stepNumber == 0)
            n << "-1\n";
        else
            n << s_stepNumber - 1 << '\n';
        DCSLog::output("STEP", n.str());
    }
}

uint64_t DCSEngine::getClockPeriod() { return clockPeriod; };
uint64_t DCSEngine::getStepNumber() { return s_stepNumber; }
void DCSEngine::setSampling(bool sampling) { DCSEngine::sampling = sampling; }
void DCSEngine::setHalfClockPeriod(uint16_t numberOfTimeSteps) {
    clockPeriod = 2 * numberOfTimeSteps;
};

void DCSEngine::programMemory(DCSRam16x8* memory, uint16_t program[16][2], bool printOut) {
    PROFILE();
    // Assuming that the ram we are going to program is the only component in the system, we want to
    // save it in a special vector so that, at the end of the procedure, when all the component are
    // erased, the ram is erased too but not lost. By doing so, more rams can be programmed and
    // stored. When all the needed rams are programmed, they can be moved to the componentVector and
    // used in the rest of the circuit.

    DCSEngine::storeRamElements();

    {
        uint64_t hcp = DCSEngine::clockPeriod / 2;

        DCSComponentArray<DCSInput> inArray0("In", memory->getNumOfInPins());
        DCSComponentArray<DCSOutput> outArray0("Out", 5);

        DCSDisplayNBits dispAddr("ADDR", 4);
        DCSDisplayNBits dispData("DATA", 8);
        DCSDisplayNBits dispOut("OUT", 8);

        inArray0.connect(memory); // control bits
        inArray0.connect(&dispData, {0, 7}, {0, 7});
        inArray0.connect(&dispAddr, {8, 11}, {0, 3});
        inArray0.connect(&outArray0, {12, 16}, {0, 4}, {"CLK", "R", "S", "WR", "OE"});
        memory->connect(&dispOut);

        inArray0[8]->makeSquareWave(2 * hcp);   // Addr 0
        inArray0[9]->makeSquareWave(4 * hcp);   //  Addr 1
        inArray0[10]->makeSquareWave(8 * hcp);  //  Addr 2
        inArray0[11]->makeSquareWave(16 * hcp); //  Addr 3
        inArray0[12]->makeSquareWave(hcp);
        inArray0[13]->makeSignal(std::string("1111000000")); // Clear - reset the ram before loading
        inArray0[14]->makeSignal(0);                         // Preset
        inArray0[15]->makeSignal(1);                         // Write
        inArray0[16]->makeSignal(0);                         // Enable

        std::stringstream s[8];
        for (int i = 0; i < 16; i++) {
            if (program[i][0] == 0) { // store pure data
                for (int j = 0; j < 8; j++) {
                    s[j] << (program[i][1] >> j & 1);
                }
            } else {                          // store instruction-data pair
                for (int j = 0; j < 4; j++) { // store instruction in MSB
                    s[j + 4] << (program[i][0] >> j & 1);
                }
                for (int j = 0; j < 4; j++) { // store data in LSB
                    s[j] << (program[i][1] >> j & 1);
                }
            }
        }
        for (int i = 0; i < 8; i++) {
            inArray0[i]->makeSignal(s[i].str(), true);
        }

        // program memory
        ramReady = true;
        DCSEngine::run(34 * hcp, true, printOut);
        ramReady = false;
        memory->disconnect();
    }

    DCSEngine::resetAndKeepRamElements();
}

void DCSEngine::programControlUnit(DCSRam256x16* memory, bool printOut) {
    PROFILE();
    const uint16_t HLT = 0b1000000000000000; // bit 15
    const uint16_t MI  = 0b0100000000000000; // bit 14
    const uint16_t RI  = 0b0010000000000000; // bit 13
    const uint16_t RO  = 0b0001000000000000; // bit 12
    const uint16_t IO  = 0b0000100000000000; // bit 11
    const uint16_t II  = 0b0000010000000000; // bit 10
    const uint16_t AI  = 0b0000001000000000; // bit 9
    const uint16_t AO  = 0b0000000100000000; // bit 8
    const uint16_t EO  = 0b0000000010000000; // bit 7
    const uint16_t SU  = 0b0000000001000000; // bit 6
    const uint16_t BI  = 0b0000000000100000; // bit 5
    const uint16_t OI  = 0b0000000000010000; // bit 4
    const uint16_t CE  = 0b0000000000001000; // bit 3
    const uint16_t CO  = 0b0000000000000100; // bit 2
    const uint16_t J   = 0b0000000000000010; // bit 1
    // const uint16_t ??  = 0b0000000000000001;

    const uint16_t data[16][8] = {
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 0000 NOP
        {MI | CO, RO | II | CE, IO | MI, RO | AI, 0, 0, 0, 0},            // 0001 LDA
        {MI | CO, RO | II | CE, IO | MI, RO | BI, EO | AI, 0, 0, 0},      // 0010 ADD
        {MI | CO, RO | II | CE, IO | MI, RO | BI, EO | AI | SU, 0, 0, 0}, // 0011 SUB
        {MI | CO, RO | II | CE, IO | MI, AO | RI, 0, 0, 0, 0},            // 0100 STA
        {MI | CO, RO | II | CE, IO | AI, 0, 0, 0, 0, 0},                  // 0101 LDI
        {MI | CO, RO | II | CE, IO | J, 0, 0, 0, 0, 0},                   // 0110
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 0111
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1000
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1001
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1010
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1011
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1100
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1101
        {MI | CO, RO | II | CE, AO | OI, 0, 0, 0, 0, 0},                  // 1110 OUT
        {MI | CO, RO | II | CE, HLT, 0, 0, 0, 0, 0}                       // 1111 HLT
    };

    DCSEngine::storeRamElements();

    {
        uint64_t hcp = DCSEngine::clockPeriod / 2;

        DCSComponentArray<DCSInput> inArray0("In", memory->getNumOfInPins());
        DCSComponentArray<DCSOutput> outArray0("Out", 5);

        DCSDisplayNBits dispAddr("ADDR", 8);
        DCSDisplayNBits dispData("DATA", 16);
        DCSDisplayNBits dispOut("OUT", 16);

        inArray0.connect(memory); // control bits
        inArray0.connect(&dispData, {0, 15}, {0, 15});
        inArray0.connect(&dispAddr, {16, 23}, {0, 7});
        inArray0.connect(&outArray0, {24, 28}, {0, 4}, {"CLK", "R", "S", "WR", "OE"});
        memory->connect(&dispOut);

        inArray0[16]->makeSquareWave(2 * hcp);   // Addr 0
        inArray0[17]->makeSquareWave(4 * hcp);   //  Addr 1
        inArray0[18]->makeSquareWave(8 * hcp);   //  Addr 2
        inArray0[19]->makeSquareWave(16 * hcp);  //  Addr 3
        inArray0[20]->makeSquareWave(32 * hcp);  //  Addr 4
        inArray0[21]->makeSquareWave(64 * hcp);  //  Addr 5
        inArray0[22]->makeSquareWave(128 * hcp); //  Addr 6
        inArray0[23]->makeSignal(0);             //  Addr 7
        inArray0[24]->makeSquareWave(hcp);
        inArray0[25]->makeSignal(std::string("11110")); // Clear - reset the ram before loading
        inArray0[26]->makeSignal(0);                    // Preset
        inArray0[27]->makeSignal(1);                    // Write
        inArray0[28]->makeSignal(0);                    // Enable

        std::stringstream s[16];
        for (int instr = 0; instr < 16; instr++) {
            for (int ucode = 0; ucode < 8; ucode++) {
                for (int bit = 0; bit < 16; bit++) {
                    s[bit] << (data[instr][ucode] >> bit & 1);
                }
            }
        }
        for (int i = 0; i < 16; i++) {
            inArray0[i]->makeSignal(s[i].str(), true);
        }

        // program memory
        ramReady = true;
        DCSEngine::run((16 * 8 * 2) * hcp, true, printOut);
        ramReady = false;
        memory->disconnect();
    }

    // restore the initial state
    DCSEngine::resetAndKeepRamElements();
}