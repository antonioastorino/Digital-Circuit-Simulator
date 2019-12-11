//
//  DCSWire.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSWire.hpp"
#include "DCSComponent.hpp"
#include <iostream>
#include <sstream>

DCSWire::DCSWire(DCSComponent* from,
				 int outPinNum,
				 DCSComponent* to,
				 int inPinNum,
				 std::string probeName)
:
from(from),
outPinNum(outPinNum),
to(to),
inPinNum(inPinNum),
probeName(probeName) {
	// TODO: make sure every component has a name != ""
	std::cout << from->getName() << " out " << outPinNum << " --> " << to->getName() << " in " << inPinNum << "\n";
}

std::string DCSWire::getProbeName() {
	return probeName;
};

void DCSWire::propagateValue() {	
	std::stringstream message;
	message << "Propagating from out " << outPinNum << " to " << to->getName() << " in " << inPinNum;
	DCSLog::info(from->getName(), message.str());
	to->setIn(from->getOutVal(outPinNum), inPinNum);
}

int DCSWire::getOutPinNum() {
	return outPinNum;
}

bool DCSWire::getOutVal() {
	return from->getOutVal(outPinNum);
}
