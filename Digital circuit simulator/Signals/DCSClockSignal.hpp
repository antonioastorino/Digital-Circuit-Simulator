//
//  DCSClockSignal.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSClockSignal_hpp
#define DCSClockSignal_hpp

class DCSClockSignal: public DCSArbitrarySignal {
private:
	ushort halfPeriod;
public:
	DCSClockSignal(ushort halfPeriod=0);
	
	bool getVal(uint32_t step) override;
};

#endif /* DCSClockSignal_hpp */
