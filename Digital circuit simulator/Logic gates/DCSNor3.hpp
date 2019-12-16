//
//  DCSNor3.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNor3_hpp
#define DCSNor3_hpp

class DCSNor3: public DCSComponent {
public:
	DCSNor3(std::string name);
	
	ushort getNumOfInPins() override {return 3; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};

#endif /* DCSNor3_hpp */
