#include "DCSComponent.hpp"
#include "DCSEngine.hpp"
#include "DCSWire.hpp"

DCSComponent::DCSComponent(std::string name, bool shouldUpdate)
    : in(0),
      out(0),
      name({name}),
      reachableIn(0),
      connectedIn(0),
      fromTristateIn(0),
      enabled(true), // only 3-state buffer can be disabled
      timeDelay(-1),
      numOfInPins(-1),
      numOfOutPins(-1),
      isNode(false),
      isTristate(false),
      initialized(false) {
    if (name == "")
        DCSLog::error("Component", "I don't have name");
    if (shouldUpdate)
        DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
    for (auto wire : wireVector) {
        delete wire;
    }
}

// set single input
void DCSComponent::setIn(bool inVal, unsigned short inPinNum) {
    if (inPinNum >= getNumOfInPins())
        throw "Input pin number out of range";
    reachableIn |= 1 << inPinNum;
    in &= (~(1 << inPinNum));  // reset inPinNum-th bit
    in |= (inVal << inPinNum); // set the same bit to inVal
}

// set entire input array
void DCSComponent::setIn(uint64_t inVec) {
    in          = inVec;
    reachableIn = getAllReachedQWord();
}

// get single output
bool DCSComponent::getOutput() {
    if (reachableIn == getAllReachedQWord())
        initialized = true;
    return out;
}

void DCSComponent::connect(DCSComponent* to, unsigned short outPinNum, unsigned short inPinNum,
                           std::string probeName) {

    DCSComponent* leftComponent  = getOutComponent(outPinNum);
    DCSComponent* rightComponent = to->getInComponent(inPinNum);

    if (leftComponent->isTristate) {
        rightComponent->setFromTristateIn(inPinNum);
    } else {
        rightComponent->setConnectedIn(inPinNum);
    }

    bool addToTheRight = true;
    for (auto component : leftComponent->rightComponentVector) {
        if (rightComponent == component) {
            addToTheRight = false;
            break;
        }
    }
    if (addToTheRight)
        leftComponent->rightComponentVector.push_back(rightComponent);

    DCSWire* wire = new DCSWire(leftComponent, rightComponent, inPinNum, probeName);

    leftComponent->wireVector.push_back(wire);
    DCSEngine::addWire(wire);
}

void DCSComponent::connect(DCSComponent* to, DCSPinNumRange outPinNumRange,
                           DCSPinNumRange inPinNumRange, std::vector<std::string> probeNames) {
    unsigned short numOfInPins  = inPinNumRange.endPinNum - inPinNumRange.startPinNum + 1;
    unsigned short numOfOutPins = outPinNumRange.endPinNum - outPinNumRange.startPinNum + 1;
    if (numOfInPins != numOfOutPins) {
        DCSLog::error(name, "Number of output pins does not coincide with number of in pins");
    }
    if (probeNames.size() == 0) {
        for (unsigned short i = 0; i < numOfInPins; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i);
        }
    } else if (probeNames.size() == 1) {
        for (unsigned short i = 0; i < numOfInPins; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i,
                          probeNames[0]);
        }
    } else {
        if (probeNames.size() != numOfInPins) {
            DCSLog::error(name, "Number probe names does not coincide with number of connections");
        }
        for (unsigned short i = 0; i < numOfInPins; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i,
                          probeNames[i]);
        }
    }
}

void DCSComponent::connect(DCSComponent* to, std::vector<std::string> probeNames) {
    unsigned short numOfOutPins = this->getNumOfOutPins();
    unsigned short numOfInPins  = to->getNumOfInPins();
    connect(to, {0, static_cast<unsigned short>(numOfOutPins - 1)},
            {0, static_cast<unsigned short>(numOfInPins - 1)}, probeNames);
}

std::string DCSComponent::getName() { return name; }

DCSComponent* DCSComponent::getInComponent(unsigned short& inPinNum) { return this; }
DCSComponent* DCSComponent::getOutComponent(unsigned short& outPinNum) { return this; }

bool DCSComponent::isInConnected(unsigned short inPinNum) { return connectedIn & (1 << inPinNum); }

bool DCSComponent::getFromTristateIn(unsigned short inPinNum) { return fromTristateIn & (1 << inPinNum); }

void DCSComponent::setConnectedIn(unsigned short inPinNum) {
    if (isInConnected(inPinNum) || getFromTristateIn(inPinNum)) {
        DCSLog::error(name, "trying to connect output to connected input");
    }
    connectedIn |= (1 << inPinNum);
}

void DCSComponent::setFromTristateIn(unsigned short inPinNum) {
    if (isInConnected(inPinNum)) {
        DCSLog::error(name, "trying to connect tristate output to connected input");
    }
    fromTristateIn |= (1 << inPinNum);
}

bool DCSComponent::propagateValues() {
    bool propagated = true;
    for (auto wire : wireVector) {
        propagated = wire->propagateValue();
    }
    return propagated;
}

bool DCSComponent::isFullyConnected() {
    return (connectedIn ^ fromTristateIn) == getAllReachedQWord();
}

uint64_t DCSComponent::getAllReachedQWord() { return (1 << getNumOfInPins()) - 1; }

bool DCSComponent::getReachableIn(unsigned short inPinNum) { return reachableIn & (1 << inPinNum); }

void DCSComponent::enable() { throw "Only 3-state buffers can access this function"; }

void DCSComponent::disable() { throw "Only 3-state buffers can access this function"; }

bool DCSComponent::getEnabled() { return enabled; }

unsigned short DCSComponent::getNumOfInPins() {
    if (numOfInPins == (unsigned short)(-1)) {
        DCSLog::error(name, "Number of input pins not set");
    }
    return numOfInPins;
}

unsigned short DCSComponent::getNumOfOutPins() {
    if (numOfOutPins == (unsigned short)(-1)) {
        DCSLog::error(name, "Number of output pins not set");
    }
    return numOfOutPins;
}

unsigned short DCSComponent::getTimeDelay() {
    if (timeDelay == (unsigned short)(-1)) {
        DCSLog::error(name, "Time delay not set");
    }
    return timeDelay;
}
