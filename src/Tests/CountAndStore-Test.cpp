#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSEngine.hpp"

void countAndStoreTest() {
	DCSLog::printTestName("Count and store");
	unsigned short clockHalfPeriod = 10;
	DCSEngine::reset(clockHalfPeriod);

	DCSUpCounterWithLoadAndAsyncSR count0("count0", 8);
	DCSRegister8Bits reg8_0("reg8_0");
	
	DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
	DCSComponentArray<DCSInput> regInArray("R-in", 5);

	DCSComponentArray<DCSOutput> outArray({"O", 8});

	// connect input array to counter
	inArray.connect(&count0);
	// connect register control inputs
	for (unsigned short i = 0; i < 5; i++) {
		regInArray.connect(&reg8_0, i, i);
	}
	// connect counter out to register data in
	for (unsigned short i = 0; i < 8; i++) {
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

