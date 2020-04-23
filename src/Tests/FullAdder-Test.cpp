//
//  FullAdder-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void fullAdderTest() {
	printTestName("Full adder");
	ushort hp = 3;
	DCSEngine::reset(hp);
	
	DCSFullAdder fa0("FA0");
	
	DCSInput in0("A");
	DCSInput in1("B");
	DCSInput in2("Cin");
	
	DCSOutput out0("Sum");
	DCSOutput out1("Cout");

	in0.connect(&fa0, 0, 0, "A");
	in1.connect(&fa0, 0, 1, "A");
	in2.connect(&fa0, 0, 2, "Cin");
	
	fa0.connect(&out0, 0,0, "Sum");
	fa0.connect(&out1, 1,0, "Cout");

	/*
	 Expected result:
	A A Cin Sum Cout    0
	1 1   1   0    0    0
	1 1   0   1    1    3
	0 1   1   0    1    6
	0 1   0   0    1    9
	1 0   1   1    0    12
	1 0   0   0    1    15
	0 0   1   1    0    18
	0 0   0   1    0    21
	1 1   1   0    0    24
	 */
	in0.makeClock(hp * 2);
	in1.makeClock(hp * 4);
	in2.makeClock();

	DCSEngine::run(hp * 9, true);
}
