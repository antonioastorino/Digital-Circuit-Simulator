//
//  DCSIO.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Use this gate to initialize the input values.
 These gates are not optional as they set the beginning of the propagation
 */

#ifndef DCSIO_hpp
#define DCSIO_hpp

#include "DCSComponent.hpp"
#include "DCSArbitrarySignal.hpp"


class DCSIO: public DCSComponent {
private:
	bool hasSignal = false;
	DCSArbitrarySignal signal;
public:
	DCSIO(bool initValue);
	DCSIO(binary_signal signal);
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};


#endif /* DCSIO_hpp */
