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
	if (from->getName() == "") {
		std::cout << from;
	}
	else {
		std::cout << from->getName();
	}
	std::cout << " out " << outPinNum << " --> ";
	if (to->getName() == "") {
		std::cout << to;
	}
	else {
		std::cout << to->getName();
	}
	std::cout<< " in " << inPinNum << "\n";
}

std::string DCSWire::getProbeName() {
	return probeName;
};

void DCSWire::propagateValue() {	
	std::stringstream message;
	message << "Propagating from out " << outPinNum << " to " << to->getName() << " in " << inPinNum;
	
	to->setIn(from->getOutVal(outPinNum), inPinNum);
}

int DCSWire::getOutPinNum() {
	return outPinNum;
}

bool DCSWire::getOutVal() {
	return from->getOutVal(outPinNum);
}
