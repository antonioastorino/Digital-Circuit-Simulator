#include "DCSAddressDecoder4Bits.hpp"
#include "DCSAnd4.hpp"
#include "DCSLog.hpp"

DCSAddressDecoder4Bits::DCSAddressDecoder4Bits(std::string name) :
DCSComponent(name, false),
nodeArray(name + "-In", 4),
notArray(name + "-Not", 4),
delArray(name + "-Del", 4),
and4Array(name + "-And4", 16) {
	for (unsigned short i = 0; i < 4; i++) {
		nodeArray.connect(&delArray, i, i);
		nodeArray.connect(&notArray, i, i);
		for (unsigned short IN = 0; IN < 16; IN ++) {
			if ((IN >> i) & 1) {
				delArray.connect(and4Array[IN], i, i);
			}
			else {
				notArray.connect(and4Array[IN], i, i);
			}
		}
	}
	
	timeDelay = 2;
	numOfInPins = 4;
	numOfOutPins = 16;
}

DCSComponent* DCSAddressDecoder4Bits::getOutComponent(unsigned short &outPinNum) {
	if (outPinNum < 16) {
		return and4Array.getOutComponent(outPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

DCSComponent* DCSAddressDecoder4Bits::getInComponent(unsigned short &inPinNum) {
	if (inPinNum < 4) {
		return nodeArray.getInComponent(inPinNum);
	}
	DCSLog::error(name, "Pin out of range");
	exit(-1);
}

void DCSAddressDecoder4Bits::updateOut() {
	DCSLog::error(name, "This function should never be called");
}
