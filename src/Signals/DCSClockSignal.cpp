
#include "DCSArbitrarySignal.hpp"
#include "DCSClockSignal.hpp"
#include "DCSEngine.hpp"

DCSClockSignal::DCSClockSignal(unsigned short halfPeriod, bool initVal):
DCSArbitrarySignal(binary_signal{0}) {
	currVal = initVal;
	if (halfPeriod) this->halfPeriod = halfPeriod;
	else this->halfPeriod = DCSEngine::getClockPeriod() / 2;
}

bool DCSClockSignal::getVal(uint32_t step) {
	if (step != counter) {
		DCSLog::error("Clock signal", "Trying to access the value in non sequential order");
		exit(-1);
	}
	counter++;
	// Shift the commutation by 1 tau because the first one is used to initialize the system
	if (step > 1) { // don't change at first step
		if (step % (halfPeriod) == 1 || halfPeriod == 1) {
			currVal = !currVal;
		}
	}
	return currVal;
}
