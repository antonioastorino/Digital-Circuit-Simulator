//
//  And6-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"

void and6Test() {
	printTestName("And 6");
	ushort hp = 2;
	DCSEngine::reset(hp);

	DCSComponentArray<DCSInput> inArray("In", 6);
	DCSAnd6 and6_0("And6_0");
	DCSOutput out0("Out0");
	
	inArray.connect(&and6_0, {"I"});
	and6_0.connect(&out0, {"O"});
	
	for (ushort i = 0; i < 6; i ++) {
		inArray[i]->makeClock(hp<<i, 0);
	}

	DCSEngine::run(64*hp+1, true);
}

