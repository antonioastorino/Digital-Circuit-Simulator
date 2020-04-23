//
//  DLatchAsyncSR-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSDLatchAsyncSR.hpp"

void dLatchAsyncSRTest() {
	printTestName("D-Latch with asynchronous SR");
	DCSEngine::reset();
	binary_signal d = {10,3,3,4};
	binary_signal en = {2,3,6,2,4};
	binary_signal reset = {18,2,5};

	
	DCSDLatchAsyncSR dLatch0("DLatch0");
	DCSComponentArray<DCSInput> inArray("In", 4);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	inArray.connect(&dLatch0, 0, 0, "DATA");
	inArray.connect(&dLatch0, 1, 1, "EN");
	inArray.connect(&dLatch0, 2, 2, "R");
	inArray.connect(&dLatch0, 3, 3, "S");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	inArray[0]->makeSignal(d);
	inArray[1]->makeSignal(en);
	inArray[2]->makeSignal(reset);
	inArray[3]->makeSignal(0);

	DCSEngine::run(25);
}
