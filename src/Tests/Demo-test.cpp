#include "DCSAnd.hpp"
#include "DCSEngine.hpp"
#include "DCSLog.hpp"

void demoTest() {
	DCSLog::printTestName("Demo 1 - And gate");
	{
		DCSAnd and0("and0");
		DCSEngine::run(5);
	}
}