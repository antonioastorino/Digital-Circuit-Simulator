//
//  DCSArbitrarySignal.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSArbitrarySignal::DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector,
									   bool synch) {
	if(levelDurationVector[0]) initVal = 0;
	else initVal = 1;
	
	uint64_t timeMultiplier = 1;
	if (synch) timeMultiplier = DCSEngine::getClockPeriod();
	
	flipBitAtSteps.reserve(levelDurationVector.size());
	
	// add length as the fist value is used to initialize
	
	totalDuration = levelDurationVector[0] * timeMultiplier + 1;
	flipBitAtSteps.push_back(totalDuration);

	for (size_t i = 1 ; i < levelDurationVector.size(); i++) {
		flipBitAtSteps.push_back(levelDurationVector[i] * timeMultiplier + flipBitAtSteps[i-1]);
		totalDuration += levelDurationVector[i] * timeMultiplier;
	}
}

bool DCSArbitrarySignal::getVal(uint32_t step) {
	if (step != counter) {
		std::cout <<
		"Error: trying to access the value in non sequential order\n";
		exit(-1);
	}
	counter++;
	if (counter > totalDuration) {
		return currVal;
	}
	if (step == flipBitAtSteps[leveNumber]) {
		leveNumber++;
		currVal = !currVal;
	}
	return currVal;
}
