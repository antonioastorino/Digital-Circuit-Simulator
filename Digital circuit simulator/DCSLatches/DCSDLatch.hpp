//
//  DCSDLatch.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 30/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
Input 0 (data) needs to be ready at least 1 td before input 1 (enable) is asserted.
Input 1 and 0 must be stable at least 2 td.
The output is stable after 4 td from the change in the input
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

#include "DCSSRLatch.hpp"
#include "DCSNot.hpp"
#include "DCSAnd.hpp"
#include "DCSNode.hpp"

class DCSDLatch: public DCSComponent {
private:
	DCSSRLatch srLatch0 = DCSSRLatch(this->name + "-SR0");
	DCSAnd and0         = DCSAnd(this->name + "-And0");
	DCSAnd and1         = DCSAnd(this->name + "-And1");
	DCSNot not0         = DCSNot(this->name + "-Not0");
	DCSNode node0       = DCSNode(this->name + "-Node0");
	DCSNode node1       = DCSNode(this->name + "-Node1");
	
public:
	DCSDLatch(std::string name);
	
	DCSComponent* getOutComponent(int &outPinNum) override;
	DCSComponent* getInComponent(int &inPinNum) override;
	void updateOut() override;
	int getTimeDelay() override { return 4; };
};

#endif /* DCSDLatch_hpp */
