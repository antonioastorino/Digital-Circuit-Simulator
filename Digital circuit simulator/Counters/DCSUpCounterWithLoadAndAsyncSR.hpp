//
//  DCSUpCounterWithLoadAndAsyncSR.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 This component is an up-counter with syncrhonous load and asynchronous clear and reset.
 Internally, there are N clock dividers which share most of the control inputs,
 hence converging to nodes.
 Input 0 (Count in) of the counter is connected to the first divider only.
 Inputs 1 to 4 are connected to the node array with indices 0 to 3, respectively.
 The other N remaining inputs (Data 0 to N-1) are numbered from 5 to 5 + N.
 Each of them is connected to input 0 (Data) of the corresponding divider.
 The outputs from 0 to N-1 (Q) correspond to output 0 (array Q) of a divider.
 Output N (array Count out) corresponds to output 2 (Count out) of the last divider.

 PINOUT:
 IN  0 - Count in (corresponding to input 5 in the internal divider)
 IN  1 - Load  - node arrray with index 0
 IN  2 - Clock - node arrray with index 1
 IN  3 - Clear - node arrray with index 2
 IN  4 - Reset - node arrray with index 3
 IN  5 - Bit 0
 IN  6 - Bit 1
 IN  ...
 IN  5 + N-1 - Bit N-1;
 OUT 0 - Bit 0
 OUT 1 - Bit 1
 ...
 OUT N-1 - Bit N-1
 OUT N - Count out

 BEHAVIORAL DESCRIPTION
 ----+------+-----+---------
  LD | C_IN | CLK | Function
 ----+------+-----+---------
   0 |   0  |  X  |  Pause
 ----+------+-----+---------
   0 |   1  |  X  |  Count
 ----+------+-----+---------
   1 |   X  |  X  |  Load
 ----+------+-----+---------
 
 Input 0 (Cout in) follows the rule of input 5 of the first divider. Therefore, it hast to be set from 3 to 1 tau before the clock rising edge. However, every Count in in the subsequent dividers is delayed by 1 tau. In addition, the output byte of the counter is ready 5 tau after the clock rising edge. As a consequence, supposing that the expected output is all 1's, the last Count in will be ready 5+N-1 tau after the clock rising edge and, as usual, has to be ready 3 tau before the next clock rising edge. Therefore, the clock period has to be at least 5+N-1+3 = 7+N tau.
 
 */

#ifndef DCSUpCounterWithLoadAndAsyncSR_hpp
#define DCSUpCounterWithLoadAndAsyncSR_hpp

class DCSUpCounterWithLoadAndAsyncSR: public DCSComponent {
private:
	DCSComponentArray<DCSClockDiv2WithEnableAndLoad> dividerArray;
	DCSComponentArray<DCSNode> nodeArray; // inputs shared among dividers
	ushort numOfElements;
	
public:
	DCSUpCounterWithLoadAndAsyncSR(std::string name,
								   ushort numOfElements);
	
	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 5 + numOfElements; };
	ushort getNumOfOutPins() override {return 1 + numOfElements; };
	
	void updateOut() override;
	int getTimeDelay() override { return 7 + numOfElements; };
};

#endif /* DCSUpCounterWithLoadAndAsyncSR_hpp */
