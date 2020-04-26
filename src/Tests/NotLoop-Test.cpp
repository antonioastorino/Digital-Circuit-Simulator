#include "DCSLog.hpp"
#include "DCSEngine.hpp"
#include "DCSNot.hpp"

void notLoopTest() {
	DCSLog::printTestName("Not loop");
	DCSEngine::reset();
	DCSNot not0("Not0");
	DCSNot not1("Not1");
	DCSNot not2("Not2");

	not0.connect(&not1, 0, 0, "N0");
	not1.connect(&not2, 0, 0, "N1");
	not2.connect(&not0, 0, 0, "N2");
	
	DCSEngine::run(11);
}
