#include "DCSLog.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSEngine.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNot.hpp"
#include "DCSAnd.hpp"

void risingEdgeDetectorTest() {
	DCSLog::printTestName("Rising edge detector");
	DCSEngine::initialize();
	DCSAnd and0("And0");
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");
	DCSUnitDelay del1("Del1");
	DCSInput in0("In0", {5,20});
	DCSOutput out0("Out0");
	
	in0.connect(&and0, 0, 0, "In");
	in0.connect(&not0, 0, 0);
	not0.connect(&del0, 0, 0);
	del0.connect(&del1, 0, 0);
	del1.connect(&and0, 0, 1);
	and0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(20);
}
