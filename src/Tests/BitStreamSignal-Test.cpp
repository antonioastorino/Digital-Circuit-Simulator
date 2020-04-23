//
//  BitStreamSignal-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void bitStreamSignalTest() {
	printTestName("Bit-stream signal");
	ushort hp = 1;
	DCSEngine::reset(hp);
	
	DCSInput in0("A");
	
	DCSOutput out0("Sum");
	
	in0.connect(&out0, 0, 0, "In0");
	
//	in0.makeSignal(std::string{"10101"}, true);
//	in0.makeSignal(binary_signal{1,1,1,1,1}, 1, true);

	in0.makeClock(3, 0);
	
	DCSEngine::run(7*hp*2, false);
}
