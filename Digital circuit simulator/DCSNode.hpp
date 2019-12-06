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

class DCSShortCiruit: public DCSComponent {
public:
	DCSShortCiruit();
	
	void updateOut() override;
	int getTimeDelay() override { return 0; }
	void setIn(bool inVal, int inPinNum) override;
	void setIn(uint64_t inVec) override;
};



#endif /* DCSNode_hpp */
