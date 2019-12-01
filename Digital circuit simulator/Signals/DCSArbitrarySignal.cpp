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
	if(levelDurationVector[0]) initVal = 0;
	else initVal = 1;
	
	flipBitAtSteps.push_back(levelDurationVector[0]); // the first variation occurs when the first level ends
	
	totalDuration = levelDurationVector[0];

	for (size_t i = 1 ; i < levelDurationVector.size(); i++) {
		flipBitAtSteps.push_back(levelDurationVector[i] + flipBitAtSteps[i-1]);
		std::cout << flipBitAtSteps[i] << "\n";
		totalDuration += levelDurationVector[i];
	}
}

bool DCSArbitrarySignal::getVal(uint32_t step) {
	if (step != counter) {
		std::cout << "Error: trying to access the value in non sequential order\n";
		exit(-1);
	}
	if (counter == totalDuration) {
		std::cout << "End of signal \n";
		exit(-2);
	}
	counter++;
	if (step == flipBitAtSteps[leveNumber]) {
		leveNumber++;
		currVal = !currVal;
	}
	return currVal;
}
