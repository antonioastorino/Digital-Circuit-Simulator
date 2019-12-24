//
//  CountAndStore-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

void countAndStoreTest() {
	printTestName("Count and store");
	ushort clockHalfPeriod = 10;
	DCSEngine::reset(clockHalfPeriod);

	DCSUpCounterWithLoadAndAsyncSR count0("count0", 8);
	DCSRegister8Bits reg8_0("reg8_0");
	
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSInput> regInArray("R-in", 5);

	DCSComponentArray<DCSOutput> outArray({"O", 8});

	// connect input array to counter
	inArray.connect(&count0);
	// connect register control inputs
	for (ushort i = 0; i < 5; i++) {
		regInArray.connect(&reg8_0, i, i);
	}
	// connect counter out to register data in
	for (ushort i = 0; i < 8; i++) {
		count0.connect(&reg8_0, i, 5 + i, "C");
	}
	reg8_0.connect(&outArray, {
		" O","O","O","O",
		"O","O","O","O"
	});
	
	// enable counting
	inArray[0]->makeSignal(1);
	// connect clock to counter
	inArray[2]->makeClock();
	// enable register output
	regInArray[0]->makeSignal(1);
	// enable register write
	regInArray[4]->makeSignal(1);
	// connect clock to register
	regInArray[1]->makeClock();
	
	DCSEngine::run(512 * clockHalfPeriod, true);
}

