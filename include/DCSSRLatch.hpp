//
//  DCSSRLatch.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 SR latch whose input pin 0 resets and 1 sets
 
 PINOUT:
 IN  0 - Reset
 IN  1 - Set
 OUT 0 - Q
 OUT 1 - !Q
*/
#ifndef DCSSRLatch_hpp
#define DCSSRLatch_hpp
#include "DCSNor.hpp"

class DCSSRLatch: public DCSComponent {
private:
	DCSNor nor0;
	DCSNor nor1;
public:
	DCSSRLatch(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	void updateOut() override;
};


#endif /* DCSSRLatch_hpp */
