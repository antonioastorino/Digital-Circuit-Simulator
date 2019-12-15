//
//  DCSArbitrarySignal.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSArbitrarySignal_hpp
#define DCSArbitrarySignal_hpp

typedef std::vector<uint64_t> binary_signal;

class DCSArbitrarySignal {
private:
	bool currVal = 0;
	bool initVal;
	uint64_t leveNumber = 0;
	uint64_t counter = 0;
	size_t totalDuration = 0;
	std::vector<uint64_t> flipBitAtSteps = {}; // stores the time at wich the level needs to change
	std::vector<uint64_t> levelDurationVector ={}; // stores the duration of each level

public:
	DCSArbitrarySignal() = delete;
	DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector,
					   bool synch = false);
	bool getVal(uint32_t step);
};

#endif /* DCSArbitrarySignal_hpp */
