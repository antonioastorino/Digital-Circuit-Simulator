//
//  DCSDLatchAsyncSR.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

/*
 Pinout:
 0 -> Data
 1 -> Enable
 2 -> Asynchronous Reset (Clear)
 3 -> Asynchronous Set (Preset)
 
 The time diagram is a merge of D-Latch and SR-Latch: when S and R are both low, this component behaves exactly like a D-Latch. When Enable is low, it behaves exactly like an SR-Latch.
 NOTE: do now use Enable when S or R are high.
 */

#ifndef DCSDLatchAsyncSR_hpp
#define DCSDLatchAsyncSR_hpp

class DCSDLatchAsyncSR: public DCSComponent {
private:
	DCSNor3 nor3_0      = DCSNor3(name + "-Nor0");
	DCSNor3 nor3_1      = DCSNor3(name + "-Nor1");
	DCSAnd and0         = DCSAnd(name + "-And0");
	DCSAnd and1         = DCSAnd(name + "-And1");
	DCSNot not0         = DCSNot(name + "-Not0");
	DCSUnitDelay del0   = DCSUnitDelay(name + "-Del0");
	DCSNode node0       = DCSNode(name + "-Node0");
	DCSNode node1       = DCSNode(name + "-Node1");
public:
	DCSDLatchAsyncSR(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 4; };
	ushort getNumOfOutPins() override {return 2; };
	
	void updateOut() override;
	int getTimeDelay() override { return 4; };
};

#endif /* DCSDLatchAsyncSR_hpp */
