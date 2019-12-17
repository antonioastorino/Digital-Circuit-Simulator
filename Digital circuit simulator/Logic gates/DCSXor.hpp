//
//  DCSXor.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 17/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSXor_hpp
#define DCSXor_hpp

class DCSXor: public DCSComponent {
public:
	DCSXor(std::string name);
	
	ushort getNumOfInPins() override {return 2; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};

#endif /* DCSXor_hpp */
