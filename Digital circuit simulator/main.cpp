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

int main(int argc, const char * argv[]) {
// 3 not in circle
/*
	DCSNot not1 = DCSNot();
	DCSNot not2 = DCSNot();
	DCSNot not3 = DCSNot();

	not1.connect(&not2, 0, 0, "N1");
	not2.connect(&not3, 0, 0, "N2");
	not3.connect(&not1, 0, 0, "N3");
*/

	
	
//	SR.setIn(1, 0);
//	SR.setIn(0, 1);

	
	binary_signal r = {4, 4, 4, 4};
	binary_signal s = {0, 4, 4, 4, 4};
	
	DCSIO I0 = DCSIO(r);
	DCSIO I1 = DCSIO(s);
	DCSSRLatch SR = DCSSRLatch();

	I0.connect(&SR, 0, 0, "I0");
	I1.connect(&SR, 0, 1, "I1");

//	for (uint32_t i = 0; i < 6; i++) {
//		std::cout << signalS.getVal(i);
//	}
//	std::cout << "\n";
//	for (uint32_t i = 0; i < 6; i++) {
//		std::cout << signalR.getVal(i);
//	}

	DCSEngine::initialize();
	DCSEngine::run(16);
	return 0;
}
