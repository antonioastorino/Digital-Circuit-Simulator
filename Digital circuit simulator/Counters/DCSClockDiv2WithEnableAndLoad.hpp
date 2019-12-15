//
//  DCSClockDiv2WithEnableAndLoad.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 This clock divider is mainly meant to be used as a building block for counters
 The minimum clock period is 10 (5 high + 5 low) tau.
 Reset and clear must be stable for at least 3 tau. Their effect is visible 3 tau after they are set.
 Inputs 0 (Data) and 1 (Load) must become stable not later than 3 tau before the clock rising edge and they have to remain stable for at least 2 tau after the that same time.
 Inputs 3 (Clear) and 4 (Preset) are directly connected to the internal JK master-slave.
 Input 5 (Count in) must be stable from not later 2 tau from the clock rising edge and stay stable from at least 2 tau after this clock transition.
 
 Output 2 (Count out) is high when input 5 and out 0 are high, with a delay of 1 tau. When connecting several dividers in cascade, this delay is multiplied by the number of dividers. This has to be taken into account when chosing the clock speed.
 
 */

#ifndef DCSClockDiv2WithEnableAndLoad_hpp
#define DCSClockDiv2WithEnableAndLoad_hpp

class DCSClockDiv2WithEnableAndLoad: public DCSComponent {
private:
	DCSNode node0  = DCSNode(name + "-Node0");
	DCSNode node1  = DCSNode(name + "-Node1");
	DCSNode node2  = DCSNode(name + "-Node2");
	DCSNot not0    = DCSNot(name + "-Not0");
	DCSNot not1    = DCSNot(name + "-Not1");
	DCSAnd and0    = DCSAnd(name + "-And0");
	DCSAnd and1    = DCSAnd(name + "-And1");
	DCSAnd and2    = DCSAnd(name + "-And2");
	DCSAnd and3    = DCSAnd(name + "-And3");
	DCSOr or0      = DCSOr(name + "-Or0");
	DCSOr or1      = DCSOr(name + "-Or1");
	DCSJKLatchMasterSlaveAsyncSR jk0 = DCSJKLatchMasterSlaveAsyncSR(name + "-JK0");
public:
	DCSClockDiv2WithEnableAndLoad(std::string name);
	
	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 6; };
	ushort getNumOfOutPins() override {return 3; };
	
	void updateOut() override;
	int getTimeDelay() override { return 9; };
};

#endif /* DCSClockDiv2WithEnableAndLoad_hpp */
