//
//  DCSDisplayNBits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSDisplayNBits_hpp
#define DCSDisplayNBits_hpp

class DCSDisplayNBits: public DCSComponent {
private:
	ushort numOfBits;
	ushort numOfDecimalDigits;
public:
	DCSDisplayNBits(std::string name, ushort numOfBits);
	void updateOut() override;
	
	ushort getNumOfInPins() override {return numOfBits; };
	ushort getNumOfOutPins() override {return 0; };
	int getTimeDelay() override { return 0; }
};

#endif /* DCSDisplayNBits_hpp */
