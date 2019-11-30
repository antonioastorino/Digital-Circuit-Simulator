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
#include "DCSIO.hpp"
#include "DCSNor.hpp"
#include "DCSSRLatch.hpp"

void latchTest() {
	binary_signal r = {0, 1, 11};
	binary_signal s = {7, 1, 3};
	
	DCSIO I0 = DCSIO(r);
	DCSIO I1 = DCSIO(s);
	DCSSRLatch SR = DCSSRLatch();

	I0.connect(&SR, 0, 0, "R");
	I1.connect(&SR, 0, 1, "S");
	
	DCSEngine::initialize();
	DCSEngine::run(11);
}

void notCascadeTest() {
	DCSNot not1 = DCSNot();
	DCSNot not2 = DCSNot();
	DCSNot not3 = DCSNot();

	not1.connect(&not2, 0, 0, "N1");
	not2.connect(&not3, 0, 0, "N2");
	not3.connect(&not1, 0, 0, "N3");
	
	DCSEngine::initialize();
	DCSEngine::run(11);
}


int main(int argc, const char * argv[]) {

	
//	latchTest();
	notCascadeTest();
	return 0;
}
