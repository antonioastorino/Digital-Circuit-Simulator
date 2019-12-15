//
//  DCSDLatch.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
Input 0 (data) needs to be ready at least 1 tau before input 1 (enable) is asserted.
Input 1 and 0 must be stable at least 2 tau.
The output is stable after 4 tau from the change in the input
Here is an example:
	  |
DATA: | X___XXXXXXXX
	  |  ^ start
	  |   __
EN:   | __  ________
	  |
	  |
Q:    | XXXX________
             _______
!Q:   | XXXXX
             ^ ready
*/

#ifndef DCSDLatch_hpp
#define DCSDLatch_hpp

class DCSDLatch: public DCSComponent {
private:
	DCSSRLatch srLatch0 = DCSSRLatch(name + "-SR0");
	DCSAnd and0         = DCSAnd(name + "-And0");
	DCSAnd and1         = DCSAnd(name + "-And1");
	DCSNot not0         = DCSNot(name + "-Not0");
	DCSUnitDelay del0   = DCSUnitDelay(name + "-Del0");
	DCSNode node0       = DCSNode(name + "-Node0");
	DCSNode node1       = DCSNode(name + "-Node1");
	
public:
	DCSDLatch(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	
	ushort getNumOfInPins() override {return 2; };
	ushort getNumOfOutPins() override {return 2; };
	
	void updateOut() override;
	int getTimeDelay() override { return 4; };
};

#endif /* DCSDLatch_hpp */
