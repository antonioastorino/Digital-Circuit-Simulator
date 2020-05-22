#include "DCSNode.hpp"
#include "DCSWire.hpp"

DCSNode::DCSNode(std::string name) : DCSComponent(name, true, true) {
    this->timeDelay    = 0;
    this->numOfInPins  = 1;
    this->numOfOutPins = 1;
}

void DCSNode::updateOut() {
    // nothing to do because the output is updated when the input changes
}

void DCSNode::setIn(bool inVal, uint16_t inPinNum) {
    DCSComponent::setIn(inVal, inPinNum);
    this->out = this->in;
    this->propagateValues();
}
