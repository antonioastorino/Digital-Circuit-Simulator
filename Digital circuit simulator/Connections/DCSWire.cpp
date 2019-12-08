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

std::string DCSWire::getProbeName() {
	return probeName;
};

void DCSWire::propagateValue() {	
//	std::cout << from << " value " << from->getOutVal(outPinNum) << " to " << to << " pin " << inPinNum << "\n";
	to->setIn(from->getOutVal(outPinNum), inPinNum);
}

int DCSWire::getOutPinNum() {
	return outPinNum;
}

bool DCSWire::getOutVal() {
	return from->getOutVal(outPinNum);
}
