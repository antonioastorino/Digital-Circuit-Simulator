//
//  DCSDFlipFlop.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

/*
Input 0 (data) needs to be ready not later than the time of input 1 (clock) assertion.
Input 1 and 0 must be stable at least 2 tau.
The output is stable after 4 tau from the change in the input
Here is an example:
	  |
DATA: | X___XXXXXXXX
	  |  ^ start
	  |  __
CLK:  | _  ________
	  |
	  |
Q:    | XXXX________
             _______
!Q:   | XXXXX
             ^ ready
*/


#ifndef DCSDFlipFlop_hpp
#define DCSDFlipFlop_hpp
#include "DCSDLatch.hpp"
class DCSNode;

class DCSDFlipFlop: public DCSComponent {
private:
	DCSNode node0;
	DCSDLatch dLat0;
	DCSAnd and0;
	DCSNot not0;
	DCSUnitDelay del0;

public:
	DCSDFlipFlop(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
};

#endif /* DCSDFlipFlop_hpp */
