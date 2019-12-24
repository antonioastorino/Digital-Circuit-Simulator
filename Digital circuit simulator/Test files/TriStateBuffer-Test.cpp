//
//  TriStateBuffer-Test.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 24/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

void triStateBufferTest() {
	printTestName("Tri-state buffer");
	DCSEngine::reset();
	
	binary_signal inputA = {3,2,2,2,2,2,100};
	binary_signal inputB = {3,3,30,3,30};
	binary_signal enableA = {2,2,2,2,2,100};
	binary_signal enableB = {2,2,2,2,2,2,100};

	DCSInput inA0("A0", 0);
	DCSInput inA1("A1", enableA, 1);
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

