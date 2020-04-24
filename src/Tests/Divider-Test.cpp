//
//  Divider-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSClockDiv2WithEnableAndLoad.hpp"
#include "DCSEngine.hpp"


void dividerTest() {
	printTestName("Divider");
	DCSEngine::reset(8);
	
	DCSClockDiv2WithEnableAndLoad div0("Div0");
	DCSComponentArray<DCSInput> inArray("In", 6);
	DCSComponentArray<DCSOutput> outArray("Out", 3);
	
	inArray.connect(&div0,{
		"D",    // 0 - D
		"LD",   // 1 - LD
		"CLK",  // 2 -CLK
		"",    // 3 - R
		"",    // 4 - S
		"C_in"  // 5 - C_in
	});
	
	inArray[0]->makeSignal(binary_signal{28,3,1});
	inArray[1]->makeSignal(binary_signal{13,2,13,3,1});
	inArray[2]->makeClock();
	inArray[3]->makeSignal(0);
	inArray[4]->makeSignal(0);
	inArray[5]->makeSignal(binary_signal{55,1});

	div0.connect(&outArray, {"Q", "!Q", "C_out"});

	DCSEngine::run(80);
}

