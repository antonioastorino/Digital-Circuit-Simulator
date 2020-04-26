#include "DCSWire.hpp"
#include "DCSLog.hpp"

DCSWire::DCSWire(DCSComponent* from,
				 DCSComponent* to,
				 unsigned short inPinNum,
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
	if (from->isEnabled()) {  // Check if a component is in high-Z state
		bool outVal = from->getOutput();
		if (to->isReachableAtIn(inPinNum)) { // If alread reached
			propagated = false;
		}
		to->setIn(outVal, inPinNum);
#if LOG_LEVEL>2
		std::stringstream message;
		message << "Sending " << outVal << " to " << to->getName() << " in " << inPinNum;
		DCSLog::debug(from->getName(), message.str());
#endif
	}
	return propagated;
}

bool DCSWire::getOutVal() {
	return from->getOutput();
}
