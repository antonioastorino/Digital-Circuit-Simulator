//
//  DCSDisplay8Bits.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 21/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSDisplay8Bits::DCSDisplay8Bits(std::string name) :
DCSComponent(name, true) {
	initialized = true; // Ensures no signal propagation from the output
}

void DCSDisplay8Bits::updateOut() {
	std::cout << name << ": ";
	for (ushort i = 0; i < 8; i++) {
		std::cout << ((in >> (7 - i)) & 1);
	}
	std::cout << "b " << in << "d";
}
