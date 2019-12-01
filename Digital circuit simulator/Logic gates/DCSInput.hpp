//
//  DCSInput.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Use this gate to initialize the input values.
 These gates are not optional as they set the beginning of the propagation
 */

#ifndef DCSInput_hpp
#define DCSInput_hpp

#include "DCSComponent.hpp"
#include "DCSArbitrarySignal.hpp"


class DCSInput: public DCSComponent {
private:
	bool hasSignal = false;
	bool constValue = 0;
	DCSArbitrarySignal signal;
public:
	DCSInput(bool initValue);
	DCSInput(binary_signal signal);
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};


#endif /* DCSInput_hpp */
