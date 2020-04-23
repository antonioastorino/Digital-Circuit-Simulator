//
//  DCSWire.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSWire.hpp"

DCSWire::DCSWire(DCSComponent* from,
				 DCSComponent* to,
				 ushort inPinNum,
				 std::string probeName):
from(from),
to(to),
inPinNum(inPinNum),
probeName(probeName) {
#if LOG_LEVEL>1
	std::stringstream s;
	s << from->getName() << " --> " << to->getName() << " in " << inPinNum;
	DCSLog::info("", s.str());
#endif
}

std::string DCSWire::getProbeName() {
	return probeName;
};

bool DCSWire::propagateValue() {
	bool propagated = true;
	if (from->getEnabled()) {  // Check if a component is in high-Z state
		bool outVal = from->getOutput();
		if (to->getReachableIn(inPinNum)) { // If alread reached
			propagated = false;
		}
		to->setIn(outVal, inPinNum);
#if LOG_LEVEL>2
		std::stringstream message;
		message << "Sending" << outVal << " to " << to->getName() << " in " << inPinNum;
		DCSLog::debug(from->getName(), message.str());
#endif
	}
	return propagated;
}

bool DCSWire::getOutVal() {
	return from->getOutput();
}
