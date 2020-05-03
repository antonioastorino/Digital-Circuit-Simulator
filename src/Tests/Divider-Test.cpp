#include "DCSClockDivider.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void dividerTest() {
    DCSLog::printTestName("Divider");
    uint16_t hcp = 8;
    DCSEngine::initialize(hcp);

    DCSClockDivider div0("Div0");
    DCSComponentArray<DCSInput> inArray("In", 6);
    DCSComponentArray<DCSOutput> outArray("Out", 3);

    inArray.connect(&div0, {
                               "D",   // 0 - D
                               "LD",  // 1 - LD
                               "CLK", // 2 -CLK
                               "",    // 3 - R
                               "",    // 4 - S
                               "C_in" // 5 - C_in
                           });

    inArray[0]->makeSignal(transitions{28, 3, 1});
    inArray[1]->makeSignal(transitions{13, 2, 13, 3, 1});
    inArray[2]->makeSquareWave(hcp);
    inArray[3]->makeSignal(0);
    inArray[4]->makeSignal(0);
    inArray[5]->makeSignal(transitions{55, 1});

    div0.connect(&outArray, {"Q", "!Q", "C_out"});

    DCSEngine::run(15 * hcp);
}
