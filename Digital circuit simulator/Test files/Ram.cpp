//
//  Ram.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 23/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

void ramTest() {
	printTestName("RAM");
	
	ushort hcp = 10; // half clock period
	DCSEngine::reset(hcp);
	DCSRam16x8                   ram0("Ram0");
	
	DCSComponentArray<DCSInput>  inArray0("In", ram0.getNumOfInPins());
	
	DCSDisplayNBits dispAddr("ADDR", 4);
	DCSDisplayNBits dispData("DATA", 8);
	DCSDisplayNBits dispCtrl("CTRL", 5);
	DCSDisplayNBits dispOut("OUT", 8);

	inArray0.connect(&ram0);
	inArray0.connect(&dispAddr, {13,16}, {0,3});
	inArray0.connect(&dispData, {5,12}, {0,7});
	inArray0.connect(&dispCtrl, {0,4}, {0,4}, {"OE", "CLK","R","S","WR"});
	ram0.connect(&dispOut);


	inArray0[0]-> makeSignal(binary_signal{ 100}, 1, true); // Enable
	inArray0[1]-> makeSignal(std::string("111111001"));
	inArray0[2]-> makeSignal(std::string("111000000")); // Clear
	inArray0[3]-> makeSignal({4,1,1}, 0, true);			// Preset
	inArray0[4]-> makeSignal(std::string("001111000")); // Write
	inArray0[5]-> makeSignal(std::string("000011100"));
	inArray0[7]-> makeSignal(std::string("000011100"));
	inArray0[15]->makeSignal({2,1,1}, 0, true);
	
	DCSEngine::run(15 * hcp, true);
}
