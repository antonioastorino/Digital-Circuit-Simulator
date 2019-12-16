//
//  DCSNor.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 26/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNor_hpp
#define DCSNor_hpp

class DCSNor: public DCSComponent {
public:
	DCSNor(std::string name);
	
	ushort getNumOfInPins() override {return 2; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};
#endif /* DCSNor_hpp */
