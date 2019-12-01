//
//  DCSOutput.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSOutput_hpp
#define DCSOutput_hpp

#include "DCSComponent.hpp"

class DCSOutput: public DCSComponent {
public:
	DCSOutput();
	void updateOut() override {};
	int getTimeDelay() override { return 0; }
};

#endif /* DCSOutput_hpp */
