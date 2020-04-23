//
//  Register8Bits-Teest.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void register8BitsTest() {
	printTestName("8-bit register");
	DCSEngine::reset();
	
	DCSRegister8Bits reg0("reg0");
	DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", reg0.getNumOfOutPins());
	
//	inArray.connect(&count0, {
//		"C_in", "LD", "CLK", "R", "S",
//		"I0", "I1", "I2", "I3"});
	inArray.connect(&reg0, {
		"OE", "CLK", "R", "S", "LD",
		"I", "I", "I", "I",
		"I", "I", "I", "I"});

	reg0.connect(&outArray,{
		" O0","O1","O2","O3",
		"O4","O5","O6","O7"});
	
//
//
	ushort clkHalfPeriod = reg0.getTimeDelay()/2+4;
	DCSEngine::setHalfClockPeriod(clkHalfPeriod);
	
	inArray[0]->makeSignal(binary_signal{3,1}, 0, true); // OE
	inArray[1]->makeClock();
	inArray[2]->makeSignal(0);
	inArray[3]->makeSignal(binary_signal{5,1}, 0, true);
	inArray[4]->makeSignal(binary_signal{1,3,1}, 0, true); // LD
	inArray[5]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[6]->makeSignal(binary_signal{1,1, 2}, 0, true);
	inArray[7]->makeSignal(binary_signal{1,1, 1, 1}, 0,true);
	inArray[8]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[9]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[10]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[11]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
	inArray[12]->makeSignal(binary_signal{1,1, 1, 1}, 0, true);
//	inArray[4]->makeSignal(0);
//	inArray[5]->makeSignal(0);
//
//
//	div0.connect(&outArray, {"Q", "!Q", "C_out"});
//
	DCSEngine::run(clkHalfPeriod * 20);
}
