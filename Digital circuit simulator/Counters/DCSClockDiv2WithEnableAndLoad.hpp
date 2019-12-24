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
 
 Inputs 0 (Data) and 1 (Load) must be stable for at least 4 tau before and 1 tau before the clock rising edge. The resulting output is displayed 5 time after the rising edge.
 Inputs 3 (Clear) and 4 (Preset) are directly connected to the internal JK master-slave. They must be stable for at least 3 tau and their effect is visible 3 tau after they are set.
 Input 5 (Count in) asserts both J and K in the internal latch with a delay of 2 tau. Therefore, it has to remain stable from 3 tau to 1 tau before the clock rising edge while Load is low.
 
 Output 2 (Count out) is high when input 5 and out 0 are high, with a delay of 1 tau. When connecting several dividers in cascade, this delay is multiplied by the number of dividers. This has to be taken into account when chosing the clock speed. When counting
 
 */

#ifndef DCSClockDiv2WithEnableAndLoad_hpp
#define DCSClockDiv2WithEnableAndLoad_hpp

class DCSClockDiv2WithEnableAndLoad: public DCSComponent {
private:
	DCSNode node0  = DCSNode(name + "-Data");
	DCSNode node1  = DCSNode(name + "-Load");
	DCSNode node2  = DCSNode(name + "-C_in");
	DCSNot not0    = DCSNot(name + "-Not0");
	DCSNot not1    = DCSNot(name + "-Not1");
	DCSAnd and0    = DCSAnd(name + "-And0");
	DCSAnd and1    = DCSAnd(name + "-And1");
	DCSAnd and2    = DCSAnd(name + "-And2");
	DCSAnd and3    = DCSAnd(name + "-C_out");
	DCSOr or0      = DCSOr(name + "-Or0");
	DCSOr or1      = DCSOr(name + "-Or1");
	DCSJKLatchMasterSlaveAsyncSR jk0 = DCSJKLatchMasterSlaveAsyncSR(name + "-JK0");
public:
	DCSClockDiv2WithEnableAndLoad(std::string name);
	
	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	void updateOut() override;
};

#endif /* DCSClockDiv2WithEnableAndLoad_hpp */
