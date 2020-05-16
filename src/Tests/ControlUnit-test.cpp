#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam256x16.hpp"
#include "DCSControlUnit4Bits.hpp"

void controlUnitTest() {
	DCSLog::printTestName("Control Unit");
    uint32_t hp = 12;
    DCSEngine::initialize(hp);
    
	DCSRam256x16 cuRam("cuRam");

	DCSEngine::programControlUnit(&cuRam);
    DCSEngine::useRamElements();


    DCSControlUnit4Bits cu0("CU", &cuRam);
    DCSComponentArray<DCSInput> inAddress("inAddress", 4);
    DCSInput inClock("inClock");
    DCSInput inReset("inReset");

    DCSDisplayNBits dispOut("out", 16);

    inClock.connect(&cu0, 0, 0);
    inReset.connect(&cu0, 0, 1);

    cu0.connect(&dispOut);
    inAddress.connect(&cu0, {0, 3}, {2, 5});

    inClock.makeSquareWave(hp);

    DCSEngine::run(40 * hp + 3, true);
}
