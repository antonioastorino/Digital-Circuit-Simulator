#include "DCSLog.hpp"
#include "DCSEngine.hpp"


void controlUnitTest() {
	DCSLog::printTestName("Control Unit");
	DCSEngine::initialize(5);
	
	
	DCSEngine::run(11);
}
