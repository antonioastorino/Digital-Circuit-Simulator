#include "DCSLog.hpp"
#include "DCSEngine.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNot.hpp"

void unitDelayTest() {
	DCSLog::printTestName("Unit delay");
	DCSEngine::reset();
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");

	not0.connect(&del0, 0, 0, "N0");
	del0.connect(&not0, 0, 0, "D0");

	DCSEngine::run(11);
}
