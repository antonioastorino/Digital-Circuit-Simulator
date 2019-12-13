//
//  DCSNode.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNode_hpp
#define DCSNode_hpp

#include "DCSComponent.hpp"

class DCSNode: public DCSComponent {
public:
	DCSNode(std::string name);
	
	void updateOut() override;
	int getTimeDelay() override { return 0; }
	void setIn(bool inVal, ushort inPinNum) override;
	void setIn(uint64_t inVec) override;
	
	ushort getNumOfInPins() override {return 1; };
	ushort getNumOfOutPins() override {return 1; };
	uint64_t getAllReachedQWord() override;
};



#endif /* DCSNode_hpp */
