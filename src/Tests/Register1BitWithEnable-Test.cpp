#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister1BitWithEnable.hpp"

void register1BitWithEnableTest() {
    DCSLog::printTestName("1-bit register with enable");
    DCSEngine::initialize(4);

    DCSRegister1BitWithEnable reg0("Reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
    DCSOutput O0("Out0");

    inArray.connect(&reg0, 0, 0, "D");
    inArray.connect(&reg0, 1, 1, "CLK");
    inArray.connect(&reg0, 2, 2, "R");
    inArray.connect(&reg0, 3, 3, "S");
    inArray.connect(&reg0, 4, 4, "LD");
    inArray.connect(&reg0, 5, 5, "OE");
    reg0.connect(&O0, 0, 0, " Q");

    inArray[0]->makeSignal(transitions{13, 3, 1});
    inArray[1]->makeSquareWave(3, true);
    inArray[2]->makeSignal(transitions{3, 40, 3, 1}, true);
    inArray[3]->makeSignal(transitions{37, 3, 1}, 0);
    inArray[4]->makeSignal(transitions{12, 4, 8, 4, 1});
    inArray[5]->makeSignal(1);

    DCSEngine::run(55, false);
}
