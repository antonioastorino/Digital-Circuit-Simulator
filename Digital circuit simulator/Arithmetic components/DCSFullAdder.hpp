//
//  DCSFullAdder.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 20/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 PINOUT
 IN  0 - A
 IN  1 - B
 IN  2 - Carry in
 
 OUT 0 - Sum
 OUT 1 - Carry out
 */

#ifndef DCSFullAdder_hpp
#define DCSFullAdder_hpp

class DCSFullAdder: public DCSComponent {
private:
	DCSNode node0;
	DCSNode node1;
	DCSNode node2;
	DCSXor xor0;
	DCSXor xor1;
	DCSAnd and0;
	DCSAnd and1;
	DCSOr or0;
public:
	DCSFullAdder(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	ushort getNumOfInPins() override {return 3; };
	ushort getNumOfOutPins() override {return 2; };
	
	int getTimeDelay() override { return 3; };
};

#endif /* DCSFullAdder_hpp */
