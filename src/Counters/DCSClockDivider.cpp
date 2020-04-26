#include "DCSLog.hpp"
#include "DCSClockDivider.hpp"

DCSClockDivider::DCSClockDivider(std::string name):
DCSComponent(name, false){
	// D
	node0.connect(&not0, 0, 0);
	node0.connect(&and0, 0, 1);
	// Load
	node1.connect(&not1, 0, 0);
	node1.connect(&and0, 0, 0);
	node1.connect(&and1, 0, 0);
	// Count in
	node2.connect(&and2, 0, 1);
	node2.connect(&and3, 0, 1);
	// Others
	not0.connect(&and1, 0, 1);
	not1.connect(&and2, 0, 0);
	and2.connect(&or0, 0, 1);
	and2.connect(&or1, 0, 1);
	and0.connect(&or0, 0, 0);
	and1.connect(&or1, 0, 0);
	or0.connect(&jk0, 0, 0); // to master J
	or1.connect(&jk0, 0, 1); // to master K
	jk0.connect(&and3, 0, 0);
	
	timeDelay = 10;
	numOfInPins = 6;
	numOfOutPins = 3;
}

DCSComponent* DCSClockDivider::getOutComponent(unsigned short &outPinNum) {
	if (outPinNum == 0 || outPinNum == 1) {
		return jk0.getOutComponent(outPinNum);
	}
	else if (outPinNum == 2) {
		outPinNum = 0;
		return &and3;
	}
	else exit(-1);
}
DCSComponent* DCSClockDivider::getInComponent(unsigned short &inPinNum) {
	switch (inPinNum) {
		case 0: // Data
			return &node0;
			break;
		case 1: // Load
			inPinNum = 0;
			return &node1;
			break;
		case 2: // CLK
			return jk0.getInComponent(inPinNum);
			break;
		case 3: // Clear
			return jk0.getInComponent(inPinNum);
			break;
		case 4: // Preset
			return jk0.getInComponent(inPinNum);
			break;
		case 5: // Enable
			inPinNum = 0;
			return &node2;
			break;
		default:
			DCSLog::error(name, "Pin out of range");
			break;
	}
	exit(-1);
}

void DCSClockDivider::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
