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
	uint64_t leveNumber;
	size_t totalDuration;
	std::vector<uint64_t> flipBitAtSteps; // stores the time at wich the level needs to change
	void fromLevelsToFlipBitAtSteps(std::vector<uint64_t> levelDurationVector,
									bool synch);
	
protected:
	uint64_t counter;
	bool currVal;
	
public:
	DCSArbitrarySignal() = delete;
	DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector,
					   bool initVal = 0,
					   bool synch = false);
	DCSArbitrarySignal(std::string zerosAndOnes,
					   bool synch = false);   
	virtual bool getVal(uint32_t step);
	~DCSArbitrarySignal();
};

#endif /* DCSArbitrarySignal_hpp */
