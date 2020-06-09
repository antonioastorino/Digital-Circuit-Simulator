#include "DCSComponent.hpp"
#include "DCSEngine.hpp"
#include "DCSWire.hpp"

DCSComponent::DCSComponent(const std::string& name, bool shouldUpdate, bool node)
    : rightComponentVector({}),
      in(0),
      out(0),
      name({name}),
      reachableIn(0),
      connectedIn(0),
      fromTristateIn(0),
      enabled(true), // only 3-state buffer can be disabled
      timeDelay(-1),
      numOfInPins(-1),
      numOfOutPins(-1),
      node(node),
      tristate(false),
      initialized(false),
      outChanged(true) {
    if (name == "") DCSLog::error("Component", 13); // I don't have a name

    if (shouldUpdate) DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
    for (auto wire : this->wireVector) {
        delete wire;
        wire = nullptr;
    }
}

// set single input
void DCSComponent::setIn(bool inVal, uint16_t inPinNum) {
    if (inPinNum >= getNumOfInPins()) DCSLog::error(this->name, 11);
    this->reachableIn |= static_cast<uint64_t>(1) << inPinNum;
    in &= (~(static_cast<uint64_t>(1) << inPinNum));  // reset inPinNum-th bit
    in |= (static_cast<uint64_t>(inVal) << inPinNum); // set the same bit to inVal
}

// get single output
bool DCSComponent::getOutput() {
    if (reachableIn == getAllReachedQWord()) this->initialized = true;
    return out;
}

void DCSComponent::connect(DCSComponent* const to, uint16_t outPinNum, uint16_t inPinNum,
                           const std::string& probeName) {
    DCSComponent* leftComponent  = getOutComponent(outPinNum);
    DCSComponent* rightComponent = to->getInComponent(inPinNum);

    if (leftComponent->isTristate()) {
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
    if (addToTheRight) leftComponent->rightComponentVector.push_back(rightComponent);

    DCSWire* wire = new DCSWire(leftComponent, rightComponent, inPinNum, probeName);
    leftComponent->wireVector.push_back(wire);
    DCSEngine::addWire(wire);
}

void DCSComponent::connect(DCSComponent* const to, DCSPinNumRange outPinNumRange,
                           DCSPinNumRange inPinNumRange,
                           const std::vector<std::string>& probeNames) {
    uint16_t nI = inPinNumRange.endPinNum - inPinNumRange.startPinNum + 1;
    uint16_t nO = outPinNumRange.endPinNum - outPinNumRange.startPinNum + 1;
    if (nI != nO) { DCSLog::error(name, 9); }
    if (probeNames.size() == 0) {
        for (uint16_t i = 0; i < nI; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i);
        }
    } else if (probeNames.size() == 1) {
        for (uint16_t i = 0; i < nI; i++) {
            std::stringstream pinName;
            pinName << probeNames[0] << i;
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i,
                          pinName.str());
        }
    } else {
        if (probeNames.size() != nI) { DCSLog::error(name, 2); }
        for (uint16_t i = 0; i < nI; i++) {
            this->connect(to, outPinNumRange.startPinNum + i, inPinNumRange.startPinNum + i,
                          probeNames[i]);
        }
    }
}

void DCSComponent::connect(DCSComponent* const to, const std::vector<std::string>& probeNames) {
    uint16_t nO = this->getNumOfOutPins();
    uint16_t nI = to->getNumOfInPins();
    this->connect(to, {0, static_cast<uint16_t>(nO - 1)}, {0, static_cast<uint16_t>(nI - 1)},
                  probeNames);
}

std::string DCSComponent::getName() const { return name; }

DCSComponent* DCSComponent::getInComponent(uint16_t& inPinNum) { return this; }
DCSComponent* DCSComponent::getOutComponent(uint16_t outPinNum) { return this; }

bool DCSComponent::isInConnected(uint16_t inPinNum) {
    return connectedIn & (static_cast<uint64_t>(1) << inPinNum);
}

bool DCSComponent::isFromTristateIn(uint16_t inPinNum) const {
    return fromTristateIn & (static_cast<uint64_t>(1) << inPinNum);
}

void DCSComponent::setConnectedIn(uint16_t inPinNum) {
    if (isInConnected(inPinNum) || isFromTristateIn(inPinNum)) { DCSLog::error(this->name, 3); }
    this->connectedIn |= (static_cast<uint64_t>(1) << inPinNum);
}

void DCSComponent::setFromTristateIn(uint16_t inPinNum) {
    if (isInConnected(inPinNum)) { DCSLog::error(this->name, 4); }
    this->fromTristateIn |= (static_cast<uint64_t>(1) << inPinNum);
}

bool DCSComponent::propagateValues() {
    for (auto wire : wireVector) {
        if (!wire->propagateValue()) return false;
    }
    return true;
}

void DCSComponent::resetUpdatedByVector() {
    for (int i = 0; i < this->numOfInPins; i++) this->updatedByVector[i] = nullptr;
}

bool DCSComponent::isReachableAtIn(uint16_t inPinNum) const {
    return reachableIn & (static_cast<uint64_t>(1) << inPinNum);
}
void DCSComponent::enable() { DCSLog::error(this->name, 5); }
void DCSComponent::disable() { DCSLog::error(this->name, 5); }
bool DCSComponent::isEnabled() const { return this->enabled; }
bool DCSComponent::isInitialized() const { return this->initialized; }
bool DCSComponent::isNode() const { return this->node; }
bool DCSComponent::isTristate() const { return this->tristate; }
bool DCSComponent::needsPropagation() const { return this->outChanged; }

void DCSComponent::checkOutputChanged(bool newOutValue) {
    this->outChanged = newOutValue != this->out;
}

bool DCSComponent::isFullyConnected() const {
    return (this->connectedIn ^ this->fromTristateIn) == this->getAllReachedQWord();
}

uint64_t DCSComponent::getAllReachedQWord() const {
    if (this->numOfInPins == 64) return static_cast<uint64_t>(-1);
    return (static_cast<uint64_t>(1) << this->numOfInPins) - 1;
}

uint16_t DCSComponent::getNumOfInPins() const {
    if (this->numOfInPins == (uint16_t)(-1)) DCSLog::error(name, 6);
    return this->numOfInPins;
}

uint16_t DCSComponent::getNumOfOutPins() const {
    if (this->numOfOutPins == (uint16_t)(-1)) DCSLog::error(name, 7);
    return this->numOfOutPins;
}

uint16_t DCSComponent::getTimeDelay() {
    if (this->timeDelay == (uint16_t)(-1)) DCSLog::error(name, 8);
    return this->timeDelay;
}
