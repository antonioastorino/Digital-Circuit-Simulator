//
//  DCSWire.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSWire.hpp"
#include "DCSComponent.hpp"
#include "DCSLog.hpp"
#include <iostream>
#include <sstream>

DCSWire::DCSWire(DCSComponent* from,
				 ushort outPinNum,
				 DCSComponent* to,
				 ushort inPinNum,
				 std::string probeName)
:
from(from),
outPinNum(outPinNum),
to(to),
inPinNum(inPinNum),
probeName(probeName) {
	std::cout << from->getName() << " out " << outPinNum << " --> " << to->getName() << " in " << inPinNum << "\n";
}

std::string DCSWire::getProbeName() {
	return probeName;
};

bool DCSWire::propagateValue() {
	bool propagated = true;
	if (from->getEnabled()) {  // Check if a component is in high-Z state
		bool outVal = from->getOutVal(outPinNum);
		std::stringstream message;
		if (to->getReachableIn(inPinNum)) {
//			message << to->getName() << " pin " << inPinNum << " already updated";
//			DCSLog::info(from->getName(), message.str());
			propagated = false;
		}
		else {
		}
		message << "Propagating " << outVal << " from out " << outPinNum << " to " << to->getName() << " in " << inPinNum;
		DCSLog::info(from->getName(), message.str());
		to->setIn(outVal, inPinNum);
	}
	return propagated;
}

ushort DCSWire::getOutPinNum() {
	return outPinNum;
}

bool DCSWire::getOutVal() {
	return from->getOutVal(outPinNum);
}
