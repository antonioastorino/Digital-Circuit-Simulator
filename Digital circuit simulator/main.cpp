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
void gateArrayTest();
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
void ramTest();

int main() {

//	srLatchTest();
//	notLoopTest();
//	unitDelayTest();
//	risingEdgeDetectorTest();
//	dFlipFlopTest();
//
//	triStateBufferTest();
//	gateArrayTest();
//	orTest();
//	nor3Test();
//	and6Test();
//	nand3Test();
//
//	dLatchTest();
//	dLatchAsyncSRTest();
//	register1BitTest();
//	jkLatchMasterSlaveAsyncSRTest();
//	dividerTest();
//	upCounterTest();
//	register8BitsTest();
//	countAndStoreTest();
	ramTest();
	return 0;
}

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

void nand3Test() {
	printTestName("Nand 3");
	DCSEngine::reset();
	
	DCSComponentArray<DCSInput> inArray("In", 3);
	DCSNand3 nand3_0("Nand3_0");
	DCSOutput out0("Out0");
	
	binary_signal in0 = {2,2,4,2,2,4,4};
	binary_signal in1 = {4,2,2,4,2,2,4};
	binary_signal in2 = {8,12};

	inArray[0]->makeSignal(in0);
	inArray[1]->makeSignal(in1);
	inArray[2]->makeSignal(in2);

	inArray.connect(&nand3_0, 0, 0, "In0");
	inArray.connect(&nand3_0, 1, 1, "In1");
	inArray.connect(&nand3_0, 2, 2, "In2");
	nand3_0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(20);
}

void and6Test() {
	printTestName("And 6");
	DCSEngine::reset(8);

	DCSComponentArray<DCSInput> inArray("In", 6);
	DCSAnd6 and6_0("And6_0");
	DCSOutput out0("Out0");
	
	inArray.connect(&and6_0, {"I"});
	and6_0.connect(&out0, {"O"});
	
	for (ushort i = 0; i < 6; i ++) {
		inArray[i]->makeClock(1<<(i+1));
	}

	DCSEngine::run(129, false);
	
}

void dLatchTest() {
	printTestName("D-Latch");
	DCSEngine::reset();
	binary_signal d = {3,7,3,3,3};
	binary_signal en = {4,2,5,2,6};
	
	DCSDLatch dLatch0("DLatch0");
	DCSInput I0("In0", d);
	DCSInput I1("In1", en);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	I0.connect(&dLatch0, 0, 0, "DATA");
	I1.connect(&dLatch0, 0, 1, "EN");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	DCSEngine::run(20);
}
void dLatchAsyncSRTest() {
	printTestName("D-Latch with asynchronous SR");
	DCSEngine::reset();
	binary_signal d = {10,3,3,4};
	binary_signal en = {2,3,6,2,4};
	binary_signal reset = {18,2,5};

	
	DCSDLatchAsyncSR dLatch0("DLatch0");
	DCSComponentArray<DCSInput> inArray("In", 4);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	inArray.connect(&dLatch0, 0, 0, "DATA");
	inArray.connect(&dLatch0, 1, 1, "EN");
	inArray.connect(&dLatch0, 2, 2, "R");
	inArray.connect(&dLatch0, 3, 3, "S");
	dLatch0.connect(&O0, 0, 0, " Q");
	dLatch0.connect(&O1, 1, 0, "!Q");
	
	inArray[0]->makeSignal(d);
	inArray[1]->makeSignal(en);
	inArray[2]->makeSignal(reset);
	inArray[3]->makeSignal(0);

	DCSEngine::run(25);
}

void jkLatchMasterSlaveAsyncSRTest() {
	printTestName("JK-Latch Master-Slave with asynchronous SR");
	DCSEngine::reset(8);
	binary_signal j = {4,2,4,2};
	binary_signal k = {0,4,2,4,2};
	binary_signal clk = {5,20,4,2,1};
	
	
	DCSJKLatchMasterSlaveAsyncSR jk0("jk0");
	DCSComponentArray<DCSInput> inArray("In", 5);
	DCSOutput O0("Out0");
	DCSOutput O1("Out1");
	
	inArray.connect(&jk0, 0, 0, "J");
	inArray.connect(&jk0, 1, 1, "K");
	inArray.connect(&jk0, 2, 2, "CLK");
	inArray.connect(&jk0, 3, 3, "");
	inArray.connect(&jk0, 4, 4, "");
	jk0.connect(&O0, 0, 0, "Q");
	jk0.connect(&O1, 1, 0, "!Q");
	
	inArray[0]->makeSignal(j);
	inArray[1]->makeSignal(k);
	inArray[2]->makeSignal(clk);
	inArray[3]->makeSignal(0);
	inArray[4]->makeSignal(0);

	DCSEngine::run(15);
}

void register1BitTest() {
	printTestName("1-bit register");
	DCSEngine::reset(5);
	
	binary_signal d{13,3,10};
	binary_signal ld{12,4,1};


	DCSRegister1Bit reg0("Reg0");
	DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
	DCSOutput O0("Out0");

	
	inArray.connect(&reg0, 0, 0, "OE");
	inArray.connect(&reg0, 1, 1, "CLK");
	inArray.connect(&reg0, 2, 2, "R");
	inArray.connect(&reg0, 3, 3, "S");
	inArray.connect(&reg0, 4, 4, "LD");
	inArray.connect(&reg0, 5, 5, "D");
	reg0.connect(&O0, 0, 0, " Q");
	
	inArray[0]->makeSignal({3,1}, true);
	inArray[1]->makeClock();
	inArray[2]->makeSignal({0,1,4,1,1}, true);
	inArray[3]->makeSignal({6,1}, true);
	inArray[4]->makeSignal(ld);
	inArray[5]->makeSignal(d);
	
	
	DCSEngine::run(100, false);
}


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
	
	inArray[0]->makeSignal({28,3,1});
	inArray[1]->makeSignal({13,2,13,3,1});
	inArray[2]->makeClock();
	inArray[3]->makeSignal(0);
	inArray[4]->makeSignal(0);
	inArray[5]->makeSignal({55,1});

	div0.connect(&outArray, {"Q", "!Q", "C_out"});

	DCSEngine::run(80);
}

void upCounterTest() {
	printTestName("Up counter");
	DCSEngine::reset();
	
	DCSUpCounterWithLoadAndAsyncSR count0("count", 8);
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
	
//	inArray.connect(&count0, {
//		"C_in", "LD", "CLK", "R", "S",
//		"I0", "I1", "I2", "I3"});
	inArray.connect(&count0, {
		"C_in", "LD", "CLK", "", "",
		"I", "I", "I", "I",
		"I", "I", "I", "I"});

	count0.connect(&outArray,{
		" O0","O1","O2","O3",
		"O4","O5","O6","O7",
		"Cout"});
	
//	
//
	DCSEngine::setHalfClockPeriod(count0.getTimeDelay()/2+1);
	inArray[0]->makeSignal({2,1}, true);
	inArray[1]->makeSignal({1,1,1}, true);
	inArray[2]->makeClock();
//	inArray[4]->makeSignal({0, 3, 1}, false);
//	inArray[5]->makeSignal({0, 1, 1}, true);
	inArray[6]->makeSignal({1,1, 1, 1}, true);
	inArray[7]->makeSignal({1,1, 1, 1}, true);
	inArray[8]->makeSignal({1,1, 1, 1}, true);
	inArray[9]->makeSignal({1,1, 1, 1}, true);
	inArray[10]->makeSignal({1,1, 1, 1}, true);
	inArray[11]->makeSignal({1,1, 1, 1}, true);
	inArray[12]->makeSignal({1,1, 1, 1}, true);
//	inArray[4]->makeSignal(0);
//	inArray[5]->makeSignal(0);
//
//	
//	div0.connect(&outArray, {"Q", "!Q", "C_out"});
//
	DCSEngine::run(160, false);
}

void register8BitsTest() {
	printTestName("8-bit register test");
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
	
	inArray[0]->makeSignal({3,1}, true); // OE
	inArray[1]->makeClock();
	inArray[2]->makeSignal(0);
	inArray[3]->makeSignal({5,1}, true);
	inArray[4]->makeSignal({1,3,1}, true); // LD
	inArray[5]->makeSignal({1,1, 1, 1}, true);
	inArray[6]->makeSignal({1,1, 2}, true);
	inArray[7]->makeSignal({1,1, 1, 1}, true);
	inArray[8]->makeSignal({1,1, 1, 1}, true);
	inArray[9]->makeSignal({1,1, 1, 1}, true);
	inArray[10]->makeSignal({1,1, 1, 1}, true);
	inArray[11]->makeSignal({1,1, 1, 1}, true);
	inArray[12]->makeSignal({1,1, 1, 1}, true);
//	inArray[4]->makeSignal(0);
//	inArray[5]->makeSignal(0);
//
//
//	div0.connect(&outArray, {"Q", "!Q", "C_out"});
//
	DCSEngine::run(clkHalfPeriod * 20);
}

void countAndStoreTest() {
	ushort clockHalfPeriod = 10;
	DCSEngine::reset(clockHalfPeriod);

	DCSUpCounterWithLoadAndAsyncSR count0("count0", 8);
	DCSRegister8Bits reg8_0("reg8_0");
	
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSInput> regInArray("R-in", 5);

	DCSComponentArray<DCSOutput> outArray({"O", 8});

	// connect input array to counter
	inArray.connect(&count0);
	// connect register control inputs
	for (ushort i = 0; i < 5; i++) {
		regInArray.connect(&reg8_0, i, i);
	}
	// connect counter out to register data in
	for (ushort i = 0; i < 8; i++) {
		count0.connect(&reg8_0, i, 5 + i, "C");
	}
	reg8_0.connect(&outArray, {
		" O","O","O","O",
		"O","O","O","O"
	});
	
	// enable counting
	inArray[0]->makeSignal(1);
	// connect clock to counter
	inArray[2]->makeClock();
	// enable register output
	regInArray[0]->makeSignal(1);
	// enable register write
	regInArray[4]->makeSignal(1);
	// connect clock to register
	regInArray[1]->makeClock();
	
	DCSEngine::run(512 * clockHalfPeriod, true);
}

void ramTest() {
	ushort hcp = 10; // half clock period
	DCSEngine::reset(hcp);
	DCSRam16x8                   ram0("Ram0");
	DCSComponentArray<DCSInput>  inArray0("In", ram0.getNumOfInPins());
	DCSComponentArray<DCSOutput> out0("Out", ram0.getNumOfOutPins());
	
	inArray0.connect(&ram0, {
		"EN",  // 0 - out enable
		"CLK", // 1 - clock
		"R",    // 2 - Reset
		"S",    // 3 - Preset
		"WR",  // 4 - Write
		"I","I","I","I","I","I","I","I", //5-12 - Data
		"A","A","A","A" // 13-16 - Address
	});
	
	ram0.connect(&out0, {"O"});
	
	inArray0[0]->makeSignal(1);
	inArray0[1]->makeClock();
	inArray0[3]->makeSignal({ 0,1,1          }, true); // Preset
	inArray0[4]->makeSignal({   2,  1,1      }, true); // Write
	inArray0[13]->makeSignal({  5,        2,1}, 1); // Address 0
	
	DCSEngine::run(200, true);

}
