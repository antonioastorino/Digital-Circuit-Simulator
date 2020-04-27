#include "DCSComponent.hpp"
#include "DCSEngine.hpp"
#include "DCSWire.hpp"

DCSComponent::DCSComponent(const std::string& name, bool shouldUpdate)
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
        DCSLog::error("Component", 13); // I don't have a name
    if (shouldUpdate)
        DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
    for (auto wire : this->wireVector) {
        delete wire;
    }
}

// set single input
void DCSComponent::setIn(bool inVal, uint16_t inPinNum) {
    if (inPinNum >= getNumOfInPins())
        DCSLog::error(this->name, 11);
    reachableIn |= 1 << inPinNum;
    in &= (~(1 << inPinNum));  // reset inPinNum-th bit
    in |= (inVal << inPinNum); // set the same bit to inVal
}

// get single output
bool DCSComponent::getOutput() {
    if (reachableIn == getAllReachedQWord())
        this->initialized = true;
    return out;
}

void DCSComponent::connect(DCSComponent* const to, uint16_t outPinNum, uint16_t inPinNum,
                           const std::string& probeName) {

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

void DCSComponent::connect(DCSComponent* const to, DCSPinNumRange outPinNumRange,
                           DCSPinNumRange inPinNumRange,
                           const std::vector<std::string>& probeNames) {
    uint16_t numOfInPins  = inPinNumRange.endPinNum - inPinNumRange.startPinNum + 1;
    uint16_t numOfOutPins = outPinNumRange.endPinNum - outPinNumRange.startPinNum + 1;
    if (numOfInPins != numOfOutPins)
        DCSLog::error(name, 9);
    if (probeNames.size() == 0) {
        for (uint16_t i = 0; i < numOfInPins; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i);
        }
    } else if (probeNames.size() == 1) {
        for (uint16_t i = 0; i < numOfInPins; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i,
                          probeNames[0]);
        }
    } else {
        if (probeNames.size() != numOfInPins) {
            DCSLog::error(name, 2);
        }
        for (uint16_t i = 0; i < numOfInPins; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i,
                          probeNames[i]);
        }
    }
}

void DCSComponent::connect(DCSComponent* const to, const std::vector<std::string>& probeNames) {
    uint16_t numOfOutPins = this->getNumOfOutPins();
    uint16_t numOfInPins  = to->getNumOfInPins();
    this->connect(to, {0, static_cast<uint16_t>(numOfOutPins - 1)},
                  {0, static_cast<uint16_t>(numOfInPins - 1)}, probeNames);
}

std::string DCSComponent::getName() { return name; }

DCSComponent* DCSComponent::getInComponent(uint16_t& inPinNum) { return this; }
DCSComponent* DCSComponent::getOutComponent(uint16_t outPinNum) { return this; }

bool DCSComponent::isInConnected(uint16_t inPinNum) { return connectedIn & (1 << inPinNum); }

bool DCSComponent::getFromTristateIn(uint16_t inPinNum) { return fromTristateIn & (1 << inPinNum); }

void DCSComponent::setConnectedIn(uint16_t inPinNum) {
    if (isInConnected(inPinNum) || getFromTristateIn(inPinNum)) {
        DCSLog::error(this->name, 3);
    }
    this->connectedIn |= (1 << inPinNum);
}

void DCSComponent::setFromTristateIn(uint16_t inPinNum) {
    if (isInConnected(inPinNum)) {
        DCSLog::error(this->name, 4);
    }
    this->fromTristateIn |= (1 << inPinNum);
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

bool DCSComponent::isReachableAtIn(uint16_t inPinNum) { return reachableIn & (1 << inPinNum); }

void DCSComponent::enable() { DCSLog::error(this->name, 5); }
void DCSComponent::disable() { DCSLog::error(this->name, 5); }

bool DCSComponent::isEnabled() { return enabled; }

uint16_t DCSComponent::getNumOfInPins() {
    if (numOfInPins == (uint16_t)(-1))
        DCSLog::error(name, 6);
    return numOfInPins;
}

uint16_t DCSComponent::getNumOfOutPins() {
    if (numOfOutPins == (uint16_t)(-1))
        DCSLog::error(name, 7);
    return numOfOutPins;
}

uint16_t DCSComponent::getTimeDelay() {
    if (timeDelay == (uint16_t)(-1))
        DCSLog::error(name, 8);
    return timeDelay;
}
