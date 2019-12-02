//
//  DCSDLatch.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSDLatch_hpp
#define DCSDLatch_hpp

#include "DCSSRLatch.hpp"
#include "DCSNot.hpp"
#include "DCSAnd.hpp"
#include "DCSShortCircuit.hpp"

class DCSDLatch: public DCSComponent {
private:
	DCSSRLatch srLatch0 = DCSSRLatch();
	DCSAnd and0 = DCSAnd();
	DCSAnd and1 = DCSAnd();
	DCSNot not0 = DCSNot();
	DCSShortCiruit D = DCSShortCiruit();
	DCSShortCiruit EN = DCSShortCiruit();

public:
	DCSDLatch();

	DCSComponent* getLeftComponent(int outPinNum) override;
	DCSComponent* getRightComponent(int &inPinNum) override;
	void updateOut() override;
	int getTimeDelay() override { return 4; };
};

#endif /* DCSDLatch_hpp */
