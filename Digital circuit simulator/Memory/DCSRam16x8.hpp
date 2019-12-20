//
//  DCSRam16x8.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Input 0: Output enable
 Input 1: Clock
 Input 2: Clear
 Input 3: Preset
 Input 4: Write
 Input 5: Data in bit 0
 Input 6: Data in bit 1
 ...
 Input 12: Data in bit 8
 Input 13: Address bit 0
 Input 14: Address bit 1
 Input 15: Address bit 2
 Input 16: Address bit 3
 
 Out   0: Data out bit 0
 Out   1: Data out bit 1
 ...
 */

#ifndef DCSRam16x8_hpp
#define DCSRam16x8_hpp

class DCSRam16x8: public DCSComponent {
private:
	DCSComponentArray<DCSRegister8Bits> regArray;
	DCSComponentArray<DCSAnd> andArray0;
	DCSComponentArray<DCSAnd> andArray1;
	DCSComponentArray<DCSNode> ctrlNodeArray;
	DCSComponentArray<DCSNode> dataNodeArray;
	DCSComponentArray<DCSNode> outNodeArray;
	DCSAddressDecoder4Bits dec0;
public:
	DCSRam16x8(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 17; }
	ushort getNumOfOutPins() override { return 8; }
	
	void updateOut() override;
	int getTimeDelay() override { return dec0.getTimeDelay() +
		regArray[0]->getTimeDelay();}
};

#endif /* DCSRam16x8_hpp */
