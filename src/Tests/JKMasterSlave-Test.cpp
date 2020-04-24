//
//  JKMasterSlave-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSEngine.hpp"
#include "DCSComponentArray.hpp"

void jkLatchMasterSlaveAsyncSRTest() {
	printTestName("JK-Latch Master-Slave with asynchronous SR");
	ushort hp = 28;
	DCSEngine::reset(hp);
		
	DCSJKLatchMasterSlaveAsyncSR jk0("jk0");
	DCSComponentArray<DCSInput> inArray("In", 5);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	inArray.connect(&jk0, {"J","K","CLK","",""});
	jk0.connect(&O0, 0, 0, "Q");
	jk0.connect(&O1, 1, 0, "!Q");
	
	inArray[0]->makeClock(hp*2, 0);
	inArray[1]->makeClock(hp*4, 0);
	inArray[2]->makeClock(hp, 0);
	inArray[3]->makeSignal(0);
	inArray[4]->makeSignal(0);

	DCSEngine::run(17*hp, true);
}
