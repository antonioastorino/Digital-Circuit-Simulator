#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"

void displayTest() {
    DCSLog::printTestName("Display");
    uint16_t hp = 1;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inArray("In", 8);

    DCSDisplayNBits disp0("Display", 8);

    for (int i = 0; i < 8; i++) {
        inArray[i]->makeSquareWave(i + 1, 0);
    }
    inArray.connect(&disp0);

    DCSEngine::run(16, false);
}
