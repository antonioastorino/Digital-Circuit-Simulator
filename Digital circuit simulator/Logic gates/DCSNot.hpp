//
//  DCSNot.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNot_hpp
#define DCSNot_hpp

class DCSNot: public DCSComponent {
public:
	DCSNot(std::string name);
	
	ushort getNumOfInPins() override {return 1; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};

#endif /* DCSNot_hpp */
