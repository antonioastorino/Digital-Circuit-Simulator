//
//  DCSRippleAdder8Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 21/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSRippleAdder8Bits_hpp
#define DCSRippleAdder8Bits_hpp

class DCSRippleAdder8Bits: public DCSComponent {
private:
	DCSComponentArray<DCSFullAdder> faArray;
public:
	DCSRippleAdder8Bits(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 17; };
	ushort getNumOfOutPins() override {return 9; };
	
	void updateOut() override;
	int getTimeDelay() override { return 14; };
};

#endif /* DCSRippleAdder8Bits_hpp */
