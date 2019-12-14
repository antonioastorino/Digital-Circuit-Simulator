//
//  DCSRegister1Bit.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Input 4 (load) must be asserted at least 1 tau before input 1 (data) changes.
 Both have to be stable at least 2 tau before the rising edge of input 3 (clock) and remain stable at least 1 extra tau.
 Inputs 2 (clear) and 3 (preset) work the same as in the SR latch. Use them with input 4 low.
 Here is an example:
	   |
 LOAD: | X____XXXXXXXX
	   |  ^ start
 DATA: | XX___XXXXXXXX
	   |     __
 CLK:  | ____  _______
			     _____
 Q:    | ________
       | _______
 !Q:   |        ______
			     ^ ready
 */

#ifndef DCSRegister1Bit_hpp
#define DCSRegister1Bit_hpp


class DCSRegister1Bit: public DCSComponent {
private:
	DCSNode node0              = DCSNode(this->name + "-Node0");
	DCSNot not0                = DCSNot(this->name + "-Not0");
	DCSAnd and0                = DCSAnd(this->name + "-And0");
	DCSAnd and1                = DCSAnd(this->name + "-And1");
	DCSOr or0                  = DCSOr(this->name + "-Or0");
	DCSDFlipFlopAsyncSR dffsr0 = DCSDFlipFlopAsyncSR(this->name + "-DFFSR0");
public:
	DCSRegister1Bit(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	ushort getNumOfInPins() override {return 5; };
	ushort getNumOfOutPins() override {return 2; };
	
	int getTimeDelay() override { return 7; };
};
#endif /* DCSRegister1Bit_hpp */

