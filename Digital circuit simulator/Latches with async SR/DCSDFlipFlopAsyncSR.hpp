//
//  DCSDFlipFlopAsyncSR.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSDFlipFlopAsyncSR_hpp
#define DCSDFlipFlopAsyncSR_hpp

class DCSDFlipFlopAsyncSR: public DCSComponent {
private:
	DCSNode node0            = DCSNode(name + "-Node0");
	DCSDLatchAsyncSR dLatSR0 = DCSDLatchAsyncSR(name + "-DLatch0");
	DCSAnd and0              = DCSAnd(name + "-And0");
	DCSNot not0              = DCSNot(name + "-Not0");
	DCSUnitDelay del0        = DCSUnitDelay(name + "-Del0");

public:
	DCSDFlipFlopAsyncSR(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	ushort getNumOfInPins() override {return 4; };
	ushort getNumOfOutPins() override {return 2; };
	
	int getTimeDelay() override { return 4; };
};


#endif /* DCSDFlipFlopAsyncSR_hpp */
