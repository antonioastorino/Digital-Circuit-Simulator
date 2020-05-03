#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSRam16x8.hpp"
#include "DCSEngine.hpp"

uint16_t LDA = 0b0000;
uint16_t ADD = 0b0001;
uint16_t OUT = 0b0010;

void firstProgramTest() {
	DCSLog::printTestName("First program");
	DCSEngine::initialize(10);

	DCSRam16x8 ram("r");
	uint16_t program[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	DCSEngine::programMemory(&ram, program);
	
	// DCSRam16x8 ram0("Ram0");
	
	
	// DCSMemoryProgrammer programmer0(&ram0);
	
	// programmer0.program(0, LDA, 14);
	// programmer0.program(1, ADD, 15);
	// programmer0.program(2, OUT, 0);
	
	// DCSComponentArray<DCSNode> bus0("Bus0", 8);
	// DCSDisplayNBits busDisplay("BUS", 8);
	// bus0.connect(&busDisplay);
	
	// DCSInput CO("CO"); // Counter OUT
	// DCSInput CE("CO"); // Counter ENABLE
	// DCSInput MI("MI"); // Memory address register IN

	// DCSUpCounterWithLoadAndAsyncSR pc0("PC0", 4);
	// DCSComponentArray<DCSInput> dummyIn0("Dummy0", 4);
	// DCSTriStateBuffer8Bits trisPC("TrisPC");
	
	// // connect PC to first 4 inputs of tris0
	// pc0.connect(&trisPC, {0,3}, {0,3});
	// // connect dummy input to the other 4 inputs of tris0
	// dummyIn0.connect(&trisPC, {0,3}, {4,7});
	// // Connect tri-state buffer to the bus
	// trisPC.connect(&bus0);
	
	// Program ram
}
