//
//  DCSDisplay8Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 21/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSDisplay8Bits_hpp
#define DCSDisplay8Bits_hpp

class DCSDisplay8Bits: public DCSComponent {
public:
	DCSDisplay8Bits(std::string name);
	void updateOut() override;
	
	ushort getNumOfInPins() override {return 8; };
	ushort getNumOfOutPins() override {return 0; };
	int getTimeDelay() override { return 0; }
};

#endif /* DCSDisplay8Bits_hpp */
