//
//  DCSAddressDecoder4Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSAddressDecoder4Bits_hpp
#define DCSAddressDecoder4Bits_hpp
#include "DCSComponentArray.hpp"
class DCSNode;
class DCSUnitDelay;
class DCSNot;
class DCSAnd4;

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
};

#endif /* DCSAddressDecoder4Bits_hpp */
