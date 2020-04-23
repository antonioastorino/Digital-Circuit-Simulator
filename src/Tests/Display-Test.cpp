//
//  Display-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"

void displayTest() {
	printTestName("Display");
	ushort hp = 1;
	DCSEngine::reset(hp);
	
	DCSComponentArray<DCSInput> inArray("In", 8);
	
	DCSDisplayNBits disp0("Display", 8);
	
	inArray[0]->makeClock(1,0);
	inArray[1]->makeClock(1,0);
	inArray.connect(&disp0);
	
	DCSEngine::run(10, false);
}
