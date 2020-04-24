//
//  Nand3-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"
#include "DCSNand3.hpp"

void nand3Test() {
	printTestName("Nand 3");
	DCSEngine::reset(1);
	
	DCSComponentArray<DCSInput> inArray("In", 3);
	DCSNand3 nand3_0("Nand3_0");
	DCSOutput out0("Out0");

	inArray[0]->makeClock(1, 0);
	inArray[1]->makeClock(2, 0);
	inArray[2]->makeClock(4, 0);

	inArray.connect(&nand3_0, 0, 0, "In0");
	inArray.connect(&nand3_0, 1, 1, "In1");
	inArray.connect(&nand3_0, 2, 2, "In2");
	nand3_0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(9);
}
