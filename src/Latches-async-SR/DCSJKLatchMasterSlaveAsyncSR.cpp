#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSLog.hpp"

DCSJKLatchMasterSlaveAsyncSR::DCSJKLatchMasterSlaveAsyncSR(std::string name) :
DCSComponent(name, false) {
	// Clock to SR master
	not0.connect(&and3_0, 0, 2);
	not0.connect(&and3_1, 0, 0);
	not0.connect(&not1, 0, 0);
	// Clock to SR slave
	not1.connect(&and0, 0, 1);
	not1.connect(&and1, 0, 0);
	// Clear
	node0.connect(&nor3_2, 0, 2);
	node0.connect(&nor3_1, 0, 2);
	// Preset
	node1.connect(&nor3_3, 0, 2);
	node1.connect(&nor3_0, 0, 2);
	// SR master
	nor3_0.connect(&nor3_1, 0, 0);
	nor3_1.connect(&nor3_0, 0, 1);
	nor3_1.connect(&and1, 0, 1);
	nor3_0.connect(&and0, 0, 0);
	// SR slave
	nor3_2.connect(&nor3_3, 0, 0);
	nor3_3.connect(&nor3_2, 0, 1);
	nor3_2.connect(&and3_1, 0, 2);
	nor3_3.connect(&and3_0, 0, 0);
	// Master to slave
	and0.connect(&nor3_2, 0, 0);
	and1.connect(&nor3_3, 0, 1);
	// Slave to master
	and3_0.connect(&nor3_0, 0, 0);
	and3_1.connect(&nor3_1, 0, 1);
	
	timeDelay = 6;
	numOfInPins = 5;
	numOfOutPins = 2;
}

DCSComponent* DCSJKLatchMasterSlaveAsyncSR::getOutComponent(uint16_t &outPinNum) {
	if (outPinNum == 0) {
		return &nor3_2;
	}
	else if (outPinNum == 1) {
		outPinNum = 0;
		return &nor3_3;
	}
	DCSLog::error(this->name, 10);
	return nullptr;
}
DCSComponent* DCSJKLatchMasterSlaveAsyncSR::getInComponent(uint16_t &inPinNum) {
	switch (inPinNum) {
		case 0: // J
			inPinNum = 1;
			return &and3_0;
			break;
		case 1: // K
			return &and3_1;
			break;
		case 2: // CLK
			inPinNum = 0;
			return &not0;
			break;
		case 3: // Clear
			inPinNum = 0;
			return &node0;
			break;
		case 4: // Preset
			inPinNum = 0;
			return &node1;
			break;
		default:
			break;
	}
	DCSLog::error(this->name, 11);
	return nullptr;
}

void DCSJKLatchMasterSlaveAsyncSR::updateOut() {
	DCSLog::error(name, 0);
}
