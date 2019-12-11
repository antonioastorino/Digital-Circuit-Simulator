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
#include "DCSDFlipFlop.hpp"


void srLatchTest() {
	binary_signal r = {3, 2, 10};
	binary_signal s = {7, 2, 6};
	
	DCSSRLatch SR = DCSSRLatch("Latch1");
	DCSInput I0 = DCSInput("In0", r);
	DCSInput I1 = DCSInput("In1", s);
	DCSOutput O0 = DCSOutput("Out0");
	DCSOutput O1 = DCSOutput("Out1");
	
	I0.connect(&SR, 0, 0, "R");
	I1.connect(&SR, 0, 1, "S");
	SR.connect(&O0, 0, 0, " Q");
	SR.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(11);
}

void notLoopTest() {
	DCSNot not0 = DCSNot("Not0");
	DCSNot not1 = DCSNot("Not1");
	DCSNot not2 = DCSNot("Not2");

	not0.connect(&not1, 0, 0, "N0");
	not1.connect(&not2, 0, 0, "N1");
	not2.connect(&not0, 0, 0, "N2");
	
	DCSEngine::run(11);
}

void sequentialNetworkTest() {
	DCSAnd and0 = DCSAnd("And0");
//	DCSAnd and1 = DCSAnd();
	
	binary_signal s0 = {1,1,1,1};
	binary_signal s1 = {1,1,1,1};
	
	DCSInput I0 = DCSInput("In0", s0);
	DCSInput I1 = DCSInput("In1", s1);
	DCSOutput O0 = DCSOutput("Out0");
	
	I0.connect(&and0, 0, 0, "I0");
	I1.connect(&and0, 0, 1, "I1");
	and0.connect(&O0, 0, 0, "O0");

	DCSEngine::run();
}

void dLatchTest() {
	binary_signal d = {0,7,3,3,3,4};
	binary_signal en = {0,2,6,2,4};
	
	DCSDLatch dLatch0 = DCSDLatch("DLatch0");
	DCSInput I0 = DCSInput("In0", d);
	DCSInput I1 = DCSInput("In1", en);
	DCSOutput O0 = DCSOutput("Out0");
	DCSOutput O1 = DCSOutput("Out1");
	
	I0.connect(&dLatch0, 0, 0, "DATA");
	I1.connect(&dLatch0, 0, 1, "EN");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(25);
}

void unitDelayTest() {
	DCSNot not0 = DCSNot("Not0");
	DCSUnitDelay del0 = DCSUnitDelay("Del0");

	not0.connect(&del0, 0, 0, "N0");
	del0.connect(&not0, 0, 0, "D0");

	DCSEngine::run(11);
}

void risingEdgeDetectorTest() {
	DCSAnd and0 = DCSAnd("And0");
	DCSNot not0 = DCSNot("Not0");
	DCSUnitDelay del0 = DCSUnitDelay("Del0");
	DCSUnitDelay del1 = DCSUnitDelay("Del1");
	DCSInput in0 = DCSInput("In0", {5,6,8});
	DCSOutput out0 = DCSOutput("Out0");
	
	in0.connect(&and0, 0, 0, "In");
	in0.connect(&not0, 0, 0);
	not0.connect(&del0, 0, 0);
	del0.connect(&del1, 0, 0);
	del1.connect(&and0, 0, 1, "!In");
	and0.connect(&out0, 0, 0, "out");
	
	DCSEngine::run(40);
}

void dFlipFlopTest() {
	binary_signal d = {4,5,10};
	binary_signal clk = {4,2,4,2,4};
	
	DCSDFlipFlop dff0 = DCSDFlipFlop("DFF0");
	DCSInput I0 = DCSInput("In0", d);
	DCSInput I1 = DCSInput("In1", clk);
	DCSOutput O0 = DCSOutput("Out0");
	DCSOutput O1 = DCSOutput("Out1");
	
	I0.connect(&dff0, 0, 0, "DATA");
	I1.connect(&dff0, 0, 1, "CLK");
	dff0.connect(&O0, 0, 0, " Q");
	dff0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(20);
}

int main() {
	DCSLog::verbose = false;

//	srLatchTest();
//	notLoopTest();
//	sequentialNetworkTest();
	dLatchTest();
//	unitDelayTest();
//	risingEdgeDetectorTest();
//	dFlipFlopTest();
	return 0;
}
