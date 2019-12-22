//
//  DCSDisplayNBits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSDisplayNBits::DCSDisplayNBits(std::string name, ushort numOfBits) :
DCSComponent(name, false),
numOfBits(numOfBits),
numOfDecimalDigits(1) {
	DCSEngine::addDisplay(this);
	initialized = true; // Ensures no signal propagation from the output
	uint64_t maxNum = (1 << numOfBits) - 1;
	while (maxNum > 9) {
		maxNum /= 10;
		numOfDecimalDigits ++;
	}
	
}

void DCSDisplayNBits::updateOut() {
	std::stringstream message;
	for (ushort i = 0; i < numOfBits; i++) {
		message << ((in >> (numOfBits - 1 - i)) & 1);
	}
	message << "b ";
	uint64_t n = 10;
	for (ushort i = 1; i < numOfDecimalDigits; i++) {
		if (in < n) message << ' ';
		n *= 10;
	}
	message << in << "d  ";
	DCSLog::output(name, message.str());
}
