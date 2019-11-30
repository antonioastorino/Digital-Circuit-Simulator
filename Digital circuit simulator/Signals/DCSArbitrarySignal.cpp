//
//  DCSArbitrarySignal.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSArbitrarySignal.hpp"
#include "DCSEngine.hpp"
#include <iostream>

DCSArbitrarySignal::DCSArbitrarySignal(std::vector<uint32_t> levelDurationVector, bool synch) {
	flipBitAtSteps.push_back(levelDurationVector[0]); // the first variation occurs when the first level ends
	for (size_t i = 1; i < levelDurationVector.size(); i++) {
		flipBitAtSteps.push_back(levelDurationVector[i] + flipBitAtSteps[i-1]);
		std::cout << flipBitAtSteps[i] << "\n";
//		std::cout << levelDurationVector[i] << "\n";
	}
}

bool DCSArbitrarySignal::getVal(uint32_t step) {
	if (step != counter) {
		std::cout << "Error: trying to access the value in non sequencial order\n";
		exit(-1);
	}
	counter++;
	if (step == flipBitAtSteps[leveNumber]) {
		leveNumber++;
		currVal = !currVal;
	}
	return currVal;
}
