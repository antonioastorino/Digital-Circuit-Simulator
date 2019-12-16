//
//  DCSJKLatchMasterSlaveAsyncSR.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Inputs 0 (J) and 1 (K) must be stable for at least 2 tau from the rising edge of
 the clock. The clock period must be at least 4 tau (with duty cicle 50%).
 The output is read 4 tau after the falling edge of the clock.
 Inputs 3 (Clear) and 4 (Preset) must be stable at least 3 tau for the reset to have effect (after 3 tau)
 Here is an example:
	   |  __
 J:    | X  XXXXXXXXX
	   | ^ start
       |  __
 K:    | X  XXXXXXXXX
	   |  __
 CLK:  | _  _________
	   |	^ stored
       |        _____
 Q:    | _______
       | ______
 !Q:   |       ______
				^ ready
 */

#ifndef DCSJKLatchMasterSlaveAsyncSR_hpp
#define DCSJKLatchMasterSlaveAsyncSR_hpp

class DCSJKLatchMasterSlaveAsyncSR: public DCSComponent {
private:
	DCSNode node0       = DCSNode(name + "-Node0");
	DCSNode node1       = DCSNode(name + "-Node1");
	DCSNode node2       = DCSNode(name + "-Node2");
	DCSAnd3 and3_0      = DCSAnd3(name + "-And3_0");
	DCSAnd3 and3_1      = DCSAnd3(name + "-And3_1");
	DCSNot not0         = DCSNot(name + "-Not0");
	DCSAnd and0         = DCSAnd(name + "-And0");
	DCSAnd and1         = DCSAnd(name + "-And1");
	DCSNor3 nor3_0      = DCSNor3(name + "-Master Q");
	DCSNor3 nor3_1      = DCSNor3(name + "-Master !Q");
	DCSNor3 nor3_2      = DCSNor3(name + "-Q");
	DCSNor3 nor3_3      = DCSNor3(name + "-!Q");
public:
	DCSJKLatchMasterSlaveAsyncSR(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 5; };
	ushort getNumOfOutPins() override {return 2; };
	
	void updateOut() override;
	int getTimeDelay() override { return 6; };
};

#endif /* DCSJKLatchMasterSlaveAsyncSR_hpp */
