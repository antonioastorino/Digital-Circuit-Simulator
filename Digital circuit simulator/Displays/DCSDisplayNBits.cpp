//
//  DCSDisplayNBits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSDisplayNBits::DCSDisplayNBits(std::string name, ushort numOfBits) :
DCSComponent(name, true),
numOfBits(numOfBits){
	initialized = true; // Ensures no signal propagation from the output
}

void DCSDisplayNBits::updateOut() {
	std::cout << name << ": ";
	for (ushort i = 0; i < numOfBits; i++) {
		std::cout << ((in >> (numOfBits - 1 - i)) & 1);
	}
	std::cout << "b " << in << "d  ";
}
