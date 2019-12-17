//
//  DCSRegister1Bit.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Input 4 (load) must be asserted at least 3 tau before the clock falling edge.
 Input 0 (Data) must be stable at least 2 tau before the clock falling edge.
 Both have to be stable for at least 1 tau after the clock falling edge.
 Inputs 2 (clear) and 3 (preset) work the same as in the SR latch. Use them with input 4 low.
 Here is an example:
	   |  ____
 LOAD: | X    XXXXXXXX
	   |  ^ start
       |   ___
 DATA: | XX   XXXXXXXX
	   | ____  _______
 CLK:  |     __
			     _____
 Q:    | ________
       | _______
 !Q:   |        ______
			     ^ ready
 
 PINOUT
 Input 0: Data
 Input 1: Clock
 Input 2: Clear
 Input 3: Preset
 Input 4: Load
 Out   0: Q
 Out   1: !Q
 */

#ifndef DCSRegister1Bit_hpp
#define DCSRegister1Bit_hpp


class DCSRegister1Bit: public DCSComponent {
private:
	DCSNode node0              = DCSNode(name + "-Load");
	DCSNot not0                = DCSNot(name + "-Data");
	DCSAnd and0                = DCSAnd(name + "-And0");
	DCSAnd and1                = DCSAnd(name + "-And1");
	DCSOr or0                  = DCSOr(name + "-Or0");
	DCSDFlipFlopAsyncSR dffsr0 = DCSDFlipFlopAsyncSR(name + "-DFFSR0");
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

