//
//  UnitDelay-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSEngine.hpp"

void unitDelayTest() {
	printTestName("Unit delay");
	DCSEngine::reset();
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");

	not0.connect(&del0, 0, 0, "N0");
	del0.connect(&not0, 0, 0, "D0");

	DCSEngine::run(11);
}
