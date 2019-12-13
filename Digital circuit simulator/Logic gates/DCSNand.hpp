//
//  DCSNand.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNand_hpp
#define DCSNand_hpp

#include "DCSComponent.hpp"

class DCSNand: public DCSComponent {
public:
	DCSNand(std::string name);
	
	ushort getNumOfInPins() override { return 2; };
	ushort getNumOfOutPins() override { return 1; };
	int getTimeDelay() override { return 1; };
	
	void updateOut() override;
};

#endif /* DCSNand_hpp */
