#include "test-RippleAdder.hpp"

void rippleAdderTest() {
	DCSLog::printTestName("8-bit ripple adder");
	uint16_t hp = 2;
	DCSEngine::initialize(hp);
	
	DCSComponentArray<DCSInput> inArray("In", 17);
	DCSRippleAdder8Bits ra0("RA");
	DCSDisplayNBits disp0("A", 8);
	DCSDisplayNBits disp1("B", 8);
	DCSDisplayNBits disp2("SUM", 8);
	DCSDisplayNBits disp3("Cout", 1);

	inArray[0]->makeSignal(1);
	inArray[1]->makeSignal(0);
	inArray[2]->makeSignal(0);
	inArray[3]->makeSignal(0);
	inArray[4]->makeSignal(0);
	inArray[5]->makeSignal(0);
	inArray[6]->makeSignal(0);
	inArray[7]->makeSignal(0);
	
	inArray[8]->makeSignal(1);
	inArray[9]->makeSignal(1);
	inArray[10]->makeSignal(1);
	inArray[11]->makeSignal(1);
	inArray[12]->makeSignal(1);
	inArray[13]->makeSignal(1);
	inArray[14]->makeSignal(1);
	inArray[15]->makeSignal(1);
	
	inArray[16]->makeSignal(0);
	inArray.connect(&disp0, {0,7}, {0,7});
	inArray.connect(&disp1, {8,15}, {0,7});
	ra0.connect(&disp2, {0,7}, {0,7});
	ra0.connect(&disp3, 8, 0);


	inArray.connect(&ra0);
	
	DCSEngine::run(16, false);
}

