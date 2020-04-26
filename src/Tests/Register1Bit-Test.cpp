#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSEngine.hpp"
#include "DCSComponentArray.hpp"

void register1BitTest() {
	DCSLog::printTestName("1-bit register");
	DCSEngine::initialize(5);
	
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
	
	inArray[0]->makeSignal(binary_signal{3,1}, 0, true);
	inArray[1]->makeClock();
	inArray[2]->makeSignal(binary_signal{1,4,1,1}, 1, true);
	inArray[3]->makeSignal(binary_signal{6,1}, 0, true);
	inArray[4]->makeSignal(ld);
	inArray[5]->makeSignal(d);
	
	DCSEngine::run(100, false);
}
