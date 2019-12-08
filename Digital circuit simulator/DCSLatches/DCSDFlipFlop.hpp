//
//  DCSDFlipFlop.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSDFlipFlop_hpp
#define DCSDFlipFlop_hpp

#include "DCSComponent.hpp"
#include "DCSDLatch.hpp"
#include "DCSAnd.hpp"
#include "DCSNot.hpp"
#include "DCSUnitDelay.hpp"

//class DCSDFlipFlop: public DCSComponent {
//private:
//	DCSDLatch lat0    = DCSDLatch();
//	DCSAnd and0       = DCSAnd();
//	DCSNot not0       = DCSNot();
//	DCSUnitDelay del0 = DCSUnitDelay();
//	
//public:
//	DCSDFlipFlop();
//	
//	DCSComponent* getOutComponent(int &outPinNum) override;
//	DCSComponent* getInComponent(int &inPinNum) override;
//	void updateOut() override;
//	int getTimeDelay() override { return 4; };
//};

#endif /* DCSDFlipFlop_hpp */
