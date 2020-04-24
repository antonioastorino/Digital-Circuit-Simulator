//
//  Or-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"

void orTest() {
	printTestName("Or");
	DCSEngine::reset(1);
	
	DCSComponentArray<DCSInput> inArray("In", 2);
	DCSOr or0("Or0");
	DCSOutput out0("Out0");
	
	binary_signal in0 = {2,2,4,10};
	binary_signal in1 = {4,2,2,10};
	
	inArray[0]->makeClock(1);
	inArray[1]->makeClock(2);
	
	inArray.connect(&or0, 0, 0, "A");
	inArray.connect(&or0, 1, 1, "B");
	or0.connect(&out0, 0, 0, "OAorB");
	
	DCSEngine::run(5);
}
