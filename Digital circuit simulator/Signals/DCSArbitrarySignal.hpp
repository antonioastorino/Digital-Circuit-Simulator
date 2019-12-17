//
//  DCSArbitrarySignal.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 levelDurationVector contains a vector of values corresponding to duration of each logical level.
 The units for the levels are:
 - tau            if synch = 0
 - clockPeriods   if synch = 1
 */


#ifndef DCSArbitrarySignal_hpp
#define DCSArbitrarySignal_hpp

class DCSArbitrarySignal {
private:
	bool initVal;
	uint64_t leveNumber = 0;
	size_t totalDuration = 0;
	std::vector<uint64_t> flipBitAtSteps = {}; // stores the time at wich the level needs to change
	std::vector<uint64_t> levelDurationVector = {}; // stores the duration of each level
	
protected:
	bool currVal = 0;
	uint64_t counter = 0;
	
public:
	DCSArbitrarySignal() = delete;
	DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector,
					   bool synch = false);
	virtual bool getVal(uint32_t step);
};

#endif /* DCSArbitrarySignal_hpp */
