#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam256x16.hpp"
#include "DCSControlUnit4Bits.hpp"

void controlUnitTest() {
	DCSLog::printTestName("Control Unit");
    uint32_t hcp = 12;
    DCSEngine::initialize(hcp);
    
	DCSRam256x16 cuRam("cuRam");

	DCSEngine::programControlUnit(&cuRam, false);
    DCSEngine::useRamElements();


    DCSControlUnit4Bits cu0("CU", &cuRam);
    DCSComponentArray<DCSInput> inAddress("inAddress", 4);
    DCSInput inClock("inClock");
    DCSInput inReset("inReset");

    DCSDisplayNBits dispOut("out", 16);
    DCSDisplayNBits dispAddr("addr", 4);

    inClock.connect(&cu0, 0, 0, "CLK");
    inReset.connect(&cu0, 0, 1);
    inAddress.connect(&dispAddr);
    cu0.connect(&dispOut);

    inAddress.connect(&cu0, {0, 3}, {2, 5});
    inAddress[0]->makeSquareWave(6*(hcp<<1));
    inAddress[1]->makeSquareWave(6*(hcp<<2));
    inAddress[2]->makeSquareWave(6*(hcp<<3));
    inAddress[3]->makeSquareWave(6*(hcp<<4));

    inClock.makeSquareWave(hcp);

    DCSEngine::run(6 * (hcp << 4) + 3, true);
}
