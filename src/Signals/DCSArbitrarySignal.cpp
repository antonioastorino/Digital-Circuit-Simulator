//
//  DCSArbitrarySignal.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSArbitrarySignal.hpp"
#include "DCSEngine.hpp"

DCSArbitrarySignal::DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector,
									   bool initVal,
									   bool synch):
leveNumber(0),
totalDuration(0),
flipBitAtSteps({}),
counter(0) {
	this->currVal = initVal;
	fromLevelsToFlipBitAtSteps(levelDurationVector, synch);
}

DCSArbitrarySignal::DCSArbitrarySignal(std::string zerosAndOnes,
									   bool synch):
leveNumber(0),
totalDuration(0),
flipBitAtSteps({}),
counter(0) {
	std::vector<uint64_t> levelDurationVector;
	uint64_t consecutive = 0;
	char currBit = zerosAndOnes[0];
	currBit == '1' ? currVal = 1 : currVal = 0;
	
	for (char ch: zerosAndOnes) {
		if (ch == currBit) {
			consecutive ++;
		}
		else {
			levelDurationVector.push_back(consecutive);
			consecutive = 1;
			currBit = ch;
		}
	}
	levelDurationVector.push_back(consecutive);
	fromLevelsToFlipBitAtSteps(levelDurationVector, synch);
	
}

void DCSArbitrarySignal::fromLevelsToFlipBitAtSteps(std::vector<uint64_t> levelDurationVector,
													bool synch) {
	uint64_t timeMultiplier = 1;
	if (synch) {
		timeMultiplier = DCSEngine::getClockPeriod();
	}
	
	flipBitAtSteps.reserve(levelDurationVector.size());
	
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

DCSArbitrarySignal::~DCSArbitrarySignal() {};
