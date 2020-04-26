#include "DCSDLatchAsyncSR.hpp"
#include "DCSLog.hpp"

DCSDLatchAsyncSR::DCSDLatchAsyncSR(std::string name) :
DCSComponent(name, false) {
	node0.connect(&del0, 0, 0);
	node0.connect(&not0, 0, 0);
	node1.connect(&and0, 0, 1);
	node1.connect(&and1, 0, 0);
	not0.connect(&and0, 0, 0);
	del0.connect(&and1, 0, 1);
	and0.connect(&nor3_0, 0, 0);
	and1.connect(&nor3_1, 0, 1);
	nor3_0.connect(&nor3_1, 0, 0);
	nor3_1.connect(&nor3_0, 0, 1);
	
	timeDelay = 4;
	numOfInPins = 4;
	numOfOutPins = 2;
}

DCSComponent* DCSDLatchAsyncSR::getOutComponent(uint16_t &outPinNum) {
	if (outPinNum == 0) return &nor3_0;
	else if (outPinNum == 1) {
		outPinNum = 0;
		return &nor3_1;
	}
	DCSLog::error(this->name, 10);
	return nullptr;
}

DCSComponent* DCSDLatchAsyncSR::getInComponent(uint16_t &inPinNum) {
	switch (inPinNum) {
		case 0:
			return &node0;
		case 1:
			inPinNum = 0;
			return &node1;
		case 2:
			return &nor3_0;
		case 3:
			inPinNum = 2;
			return &nor3_1;
		default:
			DCSLog::error(this->name, 11);
	}
	return nullptr;
}

void DCSDLatchAsyncSR::updateOut() { DCSLog::error(this->name, 0); }
