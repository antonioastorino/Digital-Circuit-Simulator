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
#include "DCSArbitrarySignal.hpp"

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
	DCSNor nor1 = DCSNor();
	DCSNor nor2 = DCSNor();
	
	DCSIO I1 = DCSIO(0);
	DCSIO I2 = DCSIO(0);

	nor1.connect(&nor2, /*out*/ 0, /*in*/ 0, "Q");
	nor2.connect(&nor1, /*out*/ 0, /*in*/ 1, "!Q");
	
	nor2.setIn(1, 0);
	nor1.setIn(0, 1);

	
	binary_signal s = {3, 3};
	binary_signal r = {0, 3, 3};
	DCSArbitrarySignal signalS = DCSArbitrarySignal(s);
	DCSArbitrarySignal signalR = DCSArbitrarySignal(r);
	for (uint32_t i = 0; i < 6; i++) {
		std::cout << signalS.getVal(i);
	}
	std::cout << "\n";
	for (uint32_t i = 0; i < 6; i++) {
		std::cout << signalR.getVal(i);
	}
	std::cout << "\n";
	DCSEngine::initialize();
	DCSEngine::run(6);
	return 0;
}
