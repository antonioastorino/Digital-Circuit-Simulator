//
//  DCSOr.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSOr_hpp
#define DCSOr_hpp

class DCSOr: public DCSComponent {
public:
	DCSOr(std::string name);
	
	ushort getNumOfInPins() override {return 2; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};
#endif /* DCSOr_hpp */
