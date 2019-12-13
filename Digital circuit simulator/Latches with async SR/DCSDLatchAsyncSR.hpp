//
//  DCSDLatchAsyncSR.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSDLatchAsyncSR_hpp
#define DCSDLatchAsyncSR_hpp

#include "DCSNor3.hpp"
#include "DCSAnd.hpp"
#include "DCSNot.hpp"
#include "DCSNode.hpp"
/*
 Pinout:
 0 -> Data
 1 -> Enable
 2 -> Asynchronous Reset
 3 -> Asynchronous Set
 */

class DCSDLatchAsyncSR: public DCSComponent {
private:
	DCSNor3 nor3_0      = DCSNor3(this->name + "-Nor0");
	DCSNor3 nor3_1      = DCSNor3(this->name + "-Nor1");
	DCSAnd and0         = DCSAnd(this->name + "-And0");
	DCSAnd and1         = DCSAnd(this->name + "-And1");
	DCSNot not0         = DCSNot(this->name + "-Not0");
	DCSNode node0       = DCSNode(this->name + "-Node0");
	DCSNode node1       = DCSNode(this->name + "-Node1");
public:
	DCSDLatchAsyncSR(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 4; };
	ushort getNumOfOutPins() override {return 2; };
	
	void updateOut() override;
	int getTimeDelay() override { return 2; };
};

#endif /* DCSDLatchAsyncSR_hpp */
