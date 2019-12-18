//
//  DCSAddressDecoder4Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSAddressDecoder4Bits_hpp
#define DCSAddressDecoder4Bits_hpp

class DCSAddressDecoder4Bits: public DCSComponent {
private:
	DCSComponentArray<DCSNode> nodeArray;
	DCSComponentArray<DCSNot> notArray;
	DCSComponentArray<DCSUnitDelay> delArray;
	DCSComponentArray<DCSAnd4> and4Array;
public:
	DCSAddressDecoder4Bits(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	ushort getNumOfInPins() override {return 4; };
	ushort getNumOfOutPins() override {return 16; };
	
	int getTimeDelay() override { return 2; };
};

#endif /* DCSAddressDecoder4Bits_hpp */
