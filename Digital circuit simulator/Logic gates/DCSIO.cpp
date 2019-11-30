//
//  DCSIO.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSIO.hpp"
#include "DCSEngine.hpp"

DCSIO::DCSIO(bool initValue) : DCSComponent(1, 1) {
	in[0] = initValue;
	DCSEngine::addInput(this);
}

void DCSIO::updateOut() {
	out[0] = in[0];
}
