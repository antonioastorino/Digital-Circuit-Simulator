//
//  main.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include <iostream>
#include "DCSHeader.h"
#include "DCSLog.hpp"
#include "DCSComponentArray.hpp"

void printTestName(std::string testName) {
	std::cout << "\n-----";
	for (int i = 0; i < testName.size(); i++) std::cout <<"-";
	std::cout << "\n" << testName << " test\n";
	for (int i = 0; i < testName.size()+5; i++) std::cout <<"-";
	std::cout << "\n";
}
	
void srLatchTest() {
	printTestName("SR-Latch");
	DCSEngine::reset();
	binary_signal s = {3, 2, 10};
	binary_signal r = {7, 2, 6};
	
	DCSSRLatch SR("Latch1");
	DCSInput I0("In0", s);
	DCSInput I1("In1", r);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&SR, 0, 0, "R");
	I1.connect(&SR, 0, 1, "S");
	SR.connect(&O0, 0, 0, " Q");
	SR.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(11);
}

void notLoopTest() {
	printTestName("Not loop");
	DCSEngine::reset();
	DCSNot not0("Not0");
	DCSNot not1("Not1");
	DCSNot not2("Not2");

	not0.connect(&not1, 0, 0, "N0");
	not1.connect(&not2, 0, 0, "N1");
	not2.connect(&not0, 0, 0, "N2");
	
	DCSEngine::run(11);
}

void dLatchTest() {
	printTestName("D-Latch");
	DCSEngine::reset();
	binary_signal d = {0,7,3,3,3,4};
	binary_signal en = {0,2,6,2,4};
	
	DCSDLatch dLatch0("DLatch0");
	DCSInput I0("In0", d);
	DCSInput I1("In1", en);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&dLatch0, 0, 0, "DATA");
	I1.connect(&dLatch0, 0, 1, "EN");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(25);
}

void unitDelayTest() {
	printTestName("Unit delay");
	DCSEngine::reset();
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");

	not0.connect(&del0, 0, 0, "N0");
	del0.connect(&not0, 0, 0, "D0");

	DCSEngine::run(11);
}

void risingEdgeDetectorTest() {
	printTestName("Rising edge detector");
	DCSEngine::reset();
	DCSAnd and0("And0");
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");
	DCSUnitDelay del1("Del1");
	DCSInput in0("In0", {5,20});
	DCSOutput out0("Out0");
	
	in0.connect(&and0, 0, 0, "In");
	in0.connect(&not0, 0, 0);
	not0.connect(&del0, 0, 0);
	del0.connect(&del1, 0, 0);
	del1.connect(&and0, 0, 1);
	and0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(20);
}

void dFlipFlopTest() {
	printTestName("D-FlipFlop");
	DCSEngine::reset();
	binary_signal d = {4,7,3,10};
	binary_signal clk = {4,2,5,2,4};
	
	DCSDFlipFlop dff0("DFF0");
	DCSInput I0("In0", d);
	DCSInput I1("In1", clk);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&dff0, 0, 0, "DATA");
	I1.connect(&dff0, 0, 1, "CLK");
	dff0.connect(&O0, 0, 0, " Q");
	dff0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(20);
}

void triStateBufferTest() {
	printTestName("Tri-state buffer");
	DCSEngine::reset();
	
	binary_signal inputA = {3,2,2,2,2,2,100};
	binary_signal inputB = {3,3,30,3,30};
	binary_signal enableA = {0,2,2,2,2,2,100};
	binary_signal enableB = {2,2,2,2,2,2,100};

	DCSInput inA0("A0", 0);
	DCSInput inA1("A1", enableA);
	DCSInput inB0("B0", 1);
	DCSInput inB1("B1", enableB);
	DCSTriStateBuffer tsbA("tsbA");
	DCSTriStateBuffer tsbB("tsbB");
	DCSNode node0("Del0");
	DCSOutput out0("Out0");

	inA0.connect(&tsbA, 0, 0, "INA");
	inA1.connect(&tsbA, 0, 1, "ENA");
	inB0.connect(&tsbB, 0, 0, "INB");
	inB1.connect(&tsbB, 0, 1, "ENB");
	tsbA.connect(&node0, 0, 0);
	tsbB.connect(&node0, 0, 0);
	node0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(20);
	
}


void gateArrayTest() {
	printTestName("Gate array");
	DCSEngine::reset();
	
	DCSComponentArray<DCSInput> inArray("In", 2);
	DCSComponentArray<DCSOutput> outArray("Out", 2);
	DCSComponentArray<DCSAnd> andArray("And", 2);
	
	inArray[0]->makeSignal(0);
	inArray[1]->makeSignal(1);

	inArray.connect(&andArray, 0, 0, "In0");
	inArray.connect(&andArray, 0, 1);
	inArray.connect(&andArray, 1, 2, "In1");
	inArray.connect(&andArray, 1, 3);
	andArray.connect(&outArray, 0, 0, "Out0");
	andArray.connect(&outArray, 1, 1, "Out1");

	DCSEngine::run(20);
}

void orTest() {
	printTestName("Or");
	DCSEngine::reset();
	
	DCSComponentArray<DCSInput> inArray("In", 2);
	DCSOr or0("Or0");
	DCSOutput out0("Out0");
	
	binary_signal in0 = {2,2,4,10};
	binary_signal in1 = {4,2,2,10};
	
	inArray[0]->makeSignal(in0);
	inArray[1]->makeSignal(in1);
	
	inArray.connect(&or0, 0, 0, "In0");
	inArray.connect(&or0, 1, 1, "In1");
	or0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run();
}

void nor3Test() {
	printTestName("Nor 3");
	DCSEngine::reset();
	
	DCSComponentArray<DCSInput> inArray("In", 3);
	DCSNor3 nor30("Nor30");
	DCSOutput out0("Out0");
	
	binary_signal in0 = {2,2,4,2,2,4,4};
	binary_signal in1 = {4,2,2,4,2,2,4};
	binary_signal in2 = {8,12};

	inArray[0]->makeSignal(in0);
	inArray[1]->makeSignal(in1);
	inArray[2]->makeSignal(in2);

	inArray.connect(&nor30, 0, 0, "In0");
	inArray.connect(&nor30, 1, 1, "In1");
	inArray.connect(&nor30, 2, 2, "In2");
	nor30.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(20);
}

int main() {
//	DCSLog::verbose = true;

//	srLatchTest();
//	notLoopTest();
//	dLatchTest();
//	unitDelayTest();
//	risingEdgeDetectorTest();
//	dFlipFlopTest();
//
//	triStateBufferTest();
//	gateArrayTest();
//	orTest();
	nor3Test();

	return 0;
}

