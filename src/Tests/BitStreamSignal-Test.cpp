#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"

void bitStreamSignalTest() {
	DCSLog::printTestName("Bit-stream signal");
	uint16_t hp = 1;
	DCSEngine::initialize(hp);
	
	DCSInput in0("A");
	
	DCSOutput out0("Sum");
	
	in0.connect(&out0, 0, 0, "In0");
	
//	in0.makeSignal(std::string{"10101"}, true);
//	in0.makeSignal(binary_signal{1,1,1,1,1}, 1, true);

	in0.makeSquareWave(3, 0);
	
	DCSEngine::run(7*hp*2, false);
}
