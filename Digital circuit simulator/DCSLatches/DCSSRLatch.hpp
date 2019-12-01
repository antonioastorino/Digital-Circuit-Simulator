//
//  DCSSRLatch.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 SR latch whose input pin 0 resets and 1 sets
 
 Schematic
 in[0] of the SR -----> in[0] of nor0
 in[1] of the SR -----> in[1] of nor1
 out[0] of nor0  -----> in[0] of nor1
 out[0] of nor1  -----> in[1] of nor0
 out[0] of nor0  -----> out[0] of SR
 out[0] of nor1  -----> out[1] of SR
*/
#ifndef DCSSRLatch_hpp
#define DCSSRLatch_hpp

#include "DCSNor.hpp"

class DCSSRLatch: public DCSComponent {
private:
	DCSNor nor0 = DCSNor();
	DCSNor nor1 = DCSNor();
public:
	DCSSRLatch();

	DCSComponent* getLeftComponent(int outPinNum) override;
	DCSComponent* getRightComponent(int &inPinNum) override;
	void updateOut() override;
	int getTimeDelay() override { return 2; };
};


#endif /* DCSSRLatch_hpp */
