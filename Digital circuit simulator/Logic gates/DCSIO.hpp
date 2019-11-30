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


class DCSIO: public DCSComponent {
public:
	DCSIO(bool initValue);
	void updateOut() override;
};


#endif /* DCSIO_hpp */
