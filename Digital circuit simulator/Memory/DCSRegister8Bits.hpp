//
//  DCSRegister8Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 17/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 
 nodeArray[0]->connect(registerArray[i], 0, 4); // Load
 nodeArray[1]->connect(registerArray[i], 0, 1); // Clock
 nodeArray[2]->connect(registerArray[i], 0, 2); // Clear
 nodeArray[3]->connect(registerArray[i], 0, 3); // Preset
 Input 0: Load
 Input 1: Clock
 Input 2: Clear
 Input 3: Preset
 Input 4: In bit 0
 Input 5: In bit 1
 ...
 
 Out   0: Out bit 0
 Out   1: Out bit 1
 ...
 */

#ifndef DCSRegister8Bits_hpp
#define DCSRegister8Bits_hpp

class DCSRegister8Bits: public DCSComponent {
private:
	DCSComponentArray<DCSRegister1Bit> registerArray;
	DCSComponentArray<DCSNode> nodeArray;
public:
	DCSRegister8Bits(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	ushort getNumOfInPins() override {return 12; };
	ushort getNumOfOutPins() override {return 8; };
	
	int getTimeDelay() override { return 7; };
};

#endif /* DCSRegister8Bits_hpp */
