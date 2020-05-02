#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSMemoryProgrammer.hpp"
#include "DCSRam16x8.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

void ramProgrammerTest() {
    DCSLog::printTestName("Ram programmer");
    DCSEngine::initialize(10);

    DCSRam16x8 ram0("Ram0");

    DCSUpCounterWithLoadAndAsyncSR count0("Count0", 4);
    DCSComponentArray<DCSInput> countIn("CountIn", count0.getNumOfInPins());
    DCSComponentArray<DCSInput> ramCtrlIn("RamCtrlIn", 5);
    DCSComponentArray<DCSInput> ramDataIn("RamDataIn", 8);

    DCSDisplayNBits dispCtrl("CTRL", 5);
    DCSDisplayNBits dispAddr("ADDR", 4);
    DCSDisplayNBits dispOut("OUT", 8);

    countIn.connect(&count0);
    ramCtrlIn.connect(&ram0, {0, 4}, {0, 4});
    ramCtrlIn.connect(&dispCtrl);
	ramDataIn.connect(&ram0, {0,7}, {5,12});
    ram0.connect(&dispOut);
    count0.connect(&ram0, {0, 3}, {13, 16});
    count0.connect(&dispAddr, {0, 3}, {0, 3});

    ramCtrlIn[0]->makeSignal(1);
    ramCtrlIn[1]->makeSquareWave(1);

    countIn[0]->makeSignal(1);
    countIn[2]->makeSquareWave(1);

    DCSMemoryProgrammer programmer(&ram0);
    for (uint16_t i = 0; i < 16; i++) {
        programmer.program(i, 3 * i + 1);
    }

    DCSEngine::run(320, true);
}
