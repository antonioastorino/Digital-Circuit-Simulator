//
//  RamProgrammer-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSRam16x8.hpp"
#include "DCSMemoryProgrammer.hpp"
#include "DCSEngine.hpp"

void ramProgrammerTest() {
	printTestName("Ram programmer");
	DCSEngine::reset(10);
	
	DCSRam16x8 ram0("Ram0");
	DCSMemoryProgrammer programmer(&ram0);
	for (ushort i = 0; i < 16; i++) {
		programmer.program(i,3*i+1);
	}
	DCSUpCounterWithLoadAndAsyncSR count0("Count0", 4);
	DCSComponentArray<DCSInput> countIn("CountIn", count0.getNumOfInPins());
	DCSComponentArray<DCSInput> ramCtrlIn("RamCtrlIn", 5);
	DCSDisplayNBits dispCtrl("CTRL", 5);
	DCSDisplayNBits dispAddr("ADDR", 4);
	DCSDisplayNBits dispOut("OUT", 8);

	countIn.connect(&count0);
	ramCtrlIn.connect(&ram0, {0,4}, {0,4});
	ramCtrlIn.connect(&dispCtrl);
	ram0.connect(&dispOut);
	count0.connect(&ram0, {0,3}, {13,16});
	count0.connect(&dispAddr, {0,3}, {0,3});

	ramCtrlIn[0] ->makeSignal(1);
	ramCtrlIn[1] ->makeClock();
	
	countIn[0] ->makeSignal(1);
	countIn[2] ->makeClock();
	
	
	DCSEngine::run(320, true);
}
