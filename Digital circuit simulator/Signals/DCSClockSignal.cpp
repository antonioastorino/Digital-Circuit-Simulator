//
//  DCSClockSignal.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSClockSignal::DCSClockSignal():
DCSArbitrarySignal({0}) { }

bool DCSClockSignal::getVal(uint32_t step) {
	if (step != counter) {
		std::cout <<
		"Error: trying to access the value in non sequential order\n";
		exit(-1);
	}
	counter++;
	// Shift the commutation by 1 tau because the first one is used to initialize the system
	if (step % (DCSEngine::getClockPeriod() / 2) == 1) {
		currVal = !currVal;
	}
	return currVal;
}
