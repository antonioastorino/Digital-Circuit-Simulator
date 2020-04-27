#include "DCSWire.hpp"
#include "DCSNode.hpp"

DCSNode::DCSNode(std::string name) :
DCSComponent(name, false) {
	isNode = true;
	
	timeDelay = 0;
	numOfInPins = 1;
	numOfOutPins = 1;
}

void DCSNode::updateOut() {
	// nothing to do because the output is updated when the input changes
}

void DCSNode::setIn(bool inVal, uint16_t inPinNum) {
	DCSComponent::setIn(inVal, inPinNum);
	out = in;
	for (auto wire_p: wireVector) {
		wire_p->propagateValue();
	}
}

uint64_t DCSNode::getAllReachedQWord() { return -1; };
