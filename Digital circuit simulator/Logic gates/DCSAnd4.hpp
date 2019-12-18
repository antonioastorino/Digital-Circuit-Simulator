//
//  DCSAnd4.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSAnd4_hpp
#define DCSAnd4_hpp

class DCSAnd4: public DCSComponent {
public:
	DCSAnd4(std::string name);
	
	ushort getNumOfInPins() override {return 4; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};

#endif /* DCSAnd4_hpp */
