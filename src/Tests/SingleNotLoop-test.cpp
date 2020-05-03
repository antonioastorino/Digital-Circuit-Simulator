#include "DCSLog.hpp"
#include "DCSEngine.hpp"
#include "DCSNot.hpp"

void singleNotLoopTest() {
	DCSLog::printTestName("Not loop");
	// Initialize engine
	DCSEngine::initialize(3);
	// Instantiate components
	DCSNot not0("Not0");
	// Connect them all
	not0.connect(&not0, 0, 0, "Not-out");
	// Run
	DCSEngine::run(11);
}











