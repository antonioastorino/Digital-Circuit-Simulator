//
//  main.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

void printTestName(std::string testName);
void srLatchTest();
void notLoopTest();
void unitDelayTest();
void risingEdgeDetectorTest();
void dFlipFlopTest();
void triStateBufferTest();
void andArrayTest();
void orTest();
void nor3Test();
void nand3Test();
void and6Test();
void dLatchTest();
void dLatchAsyncSRTest();
void jkLatchMasterSlaveAsyncSRTest();
void register1BitTest();
void dividerTest();
void upCounterTest();
void register8BitsTest();
void countAndStoreTest();
void mux2To1Test();
void fullAdderTest();
void bitStreamSignalTest();
void displayTest();
void rippleAdderTest();
void firstProgramTest();

int main() {
// TODO: make unit test
	srLatchTest();
	notLoopTest();
	unitDelayTest();
	risingEdgeDetectorTest();
	dFlipFlopTest();
	triStateBufferTest();
	andArrayTest();
	orTest();
	nor3Test();
	nand3Test();
	and6Test();
	dLatchTest();
	dLatchAsyncSRTest();
	jkLatchMasterSlaveAsyncSRTest();
	register1BitTest();
	dividerTest();
	upCounterTest();
	register8BitsTest();
	countAndStoreTest();
	mux2To1Test();
	fullAdderTest();
	bitStreamSignalTest();
	displayTest();
	rippleAdderTest();
	ramTest();
	ramProgrammerTest();
	firstProgramTest();
	
	return 0;
}

void printTestName(std::string testName) {
	std::cout << "\n-----";
	for (int i = 0; i < testName.size(); i++) std::cout <<"-";
	std::cout << "\n" << testName << " test\n";
	for (int i = 0; i < testName.size()+5; i++) std::cout <<"-";
	std::cout << "\n";
}
