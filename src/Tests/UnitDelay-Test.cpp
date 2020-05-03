#include "DCSLog.hpp"
#include "DCSEngine.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNot.hpp"

void unitDelayTest() {
	DCSLog::printTestName("Unit delay");
	DCSEngine::initialize(5);
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");

	not0.connect(&del0, {"N0"});
	del0.connect(&not0, {"D0"});

	DCSEngine::run(11);
}
