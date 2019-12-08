//
//  main.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include <iostream>
#include "DCSAnd.hpp"
#include "DCSNot.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSNor.hpp"
#include "DCSSRLatch.hpp"
#include "DCSOutput.hpp"
#include "DCSDLatch.hpp"
#include "DCSUnitDelay.hpp"

void srLatchTest() {
	binary_signal r = {3, 2, 10};
	binary_signal s = {7, 2, 6};
	
	DCSSRLatch SR = DCSSRLatch();
	DCSInput I0 = DCSInput(r);
	DCSInput I1 = DCSInput(s);
	DCSOutput O0 = DCSOutput();
	DCSOutput O1 = DCSOutput();
	
	I0.connect(&SR, 0, 0, "R");
	I1.connect(&SR, 0, 1, "S");
	SR.connect(&O0, 0, 0, " Q");
	SR.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::initialize();
	DCSEngine::run(11);
}

void notLoopTest() {
	DCSNot not0 = DCSNot();
	DCSNot not1 = DCSNot();
	DCSNot not2 = DCSNot();

	not0.connect(&not1, 0, 0, "N0");
	not1.connect(&not2, 0, 0, "N1");
	not2.connect(&not0, 0, 0, "N2");
	
	DCSEngine::initialize();
	DCSEngine::run(11);
}

void sequentialNetwork() {
	DCSAnd and0 = DCSAnd();
//	DCSAnd and1 = DCSAnd();
	
	binary_signal s0 = {1,1,1,1};
	binary_signal s1 = {1,1,1,1};
	
	DCSInput I0 = DCSInput(s0);
	DCSInput I1 = DCSInput(s1);
	DCSOutput O0 = DCSOutput();
	
	I0.connect(&and0, 0, 0, "I0");
	I1.connect(&and0, 0, 1, "I1");
	and0.connect(&O0, 0, 0, "O0");

	DCSEngine::initialize();
	DCSEngine::run();
}

void dLatchTest() {
	binary_signal d = {4,5,10};
	binary_signal en = {4,2,4,2,4};
	
	DCSDLatch dLatch = DCSDLatch();
	DCSInput I0 = DCSInput(d);
	DCSInput I1 = DCSInput(en);
	DCSOutput O0 = DCSOutput();
	DCSOutput O1 = DCSOutput();
	
	I0.connect(&dLatch, 0, 0, "DATA");
	I1.connect(&dLatch, 0, 1, "EN");
	dLatch.connect(&O0, 0, 0, " Q");
	dLatch.connect(&O1, 1, 0, "!Q");

	DCSEngine::initialize();
	DCSEngine::run(30);
}

void unitDelayTest() {
	DCSNot not0 = DCSNot();
	DCSUnitDelay del0 = DCSUnitDelay();

	not0.connect(&del0, 0, 0, "N0");
	del0.connect(&not0, 0, 0, "D0");
	
	DCSEngine::initialize();
	DCSEngine::run(11);
}

int main(int argc, const char * argv[]) {

//	srLatchTest();
//	notLoopTest();
//	sequentialNetwork();
	dLatchTest();
//	unitDelayTest();
	return 0;
}
