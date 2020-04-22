//
//  UpCounter-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

void upCounterTest() {
	printTestName("Up counter");
	DCSEngine::reset();
	
	DCSUpCounterWithLoadAndAsyncSR count0("count", 8);
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
	DCSDisplayNBits disp0("In", 8);
	DCSDisplayNBits disp1("Count", 8);

	inArray.connect(&count0, {
		"C_in", "LD", "CLK", "", "",
		"", "", "", "",
		"", "", "", ""});

	count0.connect(&outArray,{
		"","","","",
		"","","","",
		"Cout"});
	
	inArray.connect(&disp0, {5, 12}, {0, 7});
	count0.connect(&disp1, {0, 7}, {0, 7});
	
	ushort hp = count0.getTimeDelay()/2+1;
	DCSEngine::setHalfClockPeriod(hp);
	inArray[0]->makeSignal(binary_signal{2,1}, 0, true);
	inArray[1]->makeSignal(binary_signal{1,1,1}, 0, true);
	inArray[2]->makeClock();

	inArray[6]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[7]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[8]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[9]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[10]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[11]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[12]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);

	DCSEngine::run(265 * hp * 2, false);
}

