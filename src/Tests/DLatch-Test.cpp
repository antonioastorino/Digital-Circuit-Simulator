//
//  DLatch-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSDLatch.hpp"
#include "DCSEngine.hpp"

void dLatchTest() {
	printTestName("D-Latch");
	DCSEngine::reset();
	binary_signal d = {3,7,3,3,3};
	binary_signal en = {4,2,5,2,6};
	
	DCSDLatch dLatch0("DLatch0");
	DCSInput I0("In0", d);
	DCSInput I1("In1", en);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&dLatch0, 0, 0, "DATA");
	I1.connect(&dLatch0, 0, 1, "EN");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(20);
}
