#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister8BitsWithEnable.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

void countAndStoreTest() {
    DCSLog::printTestName("Count and store");
    uint16_t hp = 18;
    DCSEngine::initialize(hp);

    DCSUpCounterWithLoadAndAsyncSR count0("count0", 8);
    DCSRegister8BitsWithEnable reg8_0("reg8_0");
    DCSDisplayNBits disp0("DATA", 8);
    DCSDisplayNBits disp1("OUT", 8);
    DCSDisplayNBits disp2("COUT", 9);

    DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
    DCSComponentArray<DCSInput> regInArray("R-in", 5);

    DCSComponentArray<DCSOutput> outArray({"O", 8});

    // connect input array to counter
    inArray.connect(&count0, {0, 4}, {0, 4}, {"c", "LD", "CLK", "R", "S"});
    inArray.connect(&count0, {5, 12}, {5, 12});
    inArray.connect(&disp0, {5, 12}, {0, 7});
    // connect register control inputs
    regInArray.connect(&reg8_0, {0, 4}, {0, 4});
    // connect counter out to register data in
    count0.connect(&reg8_0, {0, 7}, {5, 12});
    count0.connect(&disp2);
    reg8_0.connect(&outArray);

	reg8_0.connect(&disp1);

    inArray[0]->makeSignal(1); // enable counting
    // connect clock to counter
    inArray[2]->makeSquareWave(hp);
    // inArray[3]->makeSignal({1,1},1,1);// enable register write
    // enable register output
    regInArray[0]->makeSignal(1);
    regInArray[4]->makeSignal(1);
    // connect clock to register
    regInArray[1]->makeSquareWave(hp);

    DCSEngine::run(514 * hp, true);
}
