#include "DCSALU.hpp"
#include "DCSAddressDecoder4Bits.hpp"
#include "DCSAddressDecoder8Bits.hpp"
#include "DCSAnd6.hpp"
#include "DCSClockDivider.hpp"
#include "DCSComponentArray.hpp"
#include "DCSControlUnit4Bits.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSDLatch.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSFullAdder.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSLog.hpp"
#include "DCSMux2To1.hpp"
#include "DCSNand3.hpp"
#include "DCSNor3.hpp"
#include "DCSNot.hpp"
#include "DCSRam16x8.hpp"
#include "DCSTimer.hpp"
#include "DCSOr.hpp"
#include "DCSRam256x16.hpp"
#include "DCSRegister16BitsWithEnable.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSRegister1BitWithEnable.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSRegister8BitsWithEnable.hpp"
#include "DCSRippleAdder8Bits.hpp"
#include "test-SRLatch.hpp"
#include "test-TriStateBuffer.hpp"
#include "test-UnitDelay.hpp"
#include "test-UpCounter.hpp"
#include "test-UpCounter4Bits.hpp"
#include "test-Xor.hpp"
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    std::vector<func_descriptor> tests = {
        FUNC_CONSTRUCTOR(bitStreamSignalTest),
        FUNC_CONSTRUCTOR(orTest),
        FUNC_CONSTRUCTOR(unitDelayTest),
        FUNC_CONSTRUCTOR(nor3Test),
        FUNC_CONSTRUCTOR(notLoopTest),
        FUNC_CONSTRUCTOR(nand3Test),
        FUNC_CONSTRUCTOR(andArrayTest),
        FUNC_CONSTRUCTOR(and6Test),
        FUNC_CONSTRUCTOR(srLatchTest),
        FUNC_CONSTRUCTOR(triStateBufferTest),
        FUNC_CONSTRUCTOR(dLatchTest),
        FUNC_CONSTRUCTOR(dLatchAsyncSRTest),
        FUNC_CONSTRUCTOR(dFlipFlopTest),
        FUNC_CONSTRUCTOR(register1BitWithEnableTest),
        FUNC_CONSTRUCTOR(register8BitsWithEnableTest),
        FUNC_CONSTRUCTOR(jkLatchMasterSlaveAsyncSRTest),
        FUNC_CONSTRUCTOR(dividerTest),
        FUNC_CONSTRUCTOR(upCounterTest),
        FUNC_CONSTRUCTOR(mux2To1Test),
        FUNC_CONSTRUCTOR(fullAdderTest),
        FUNC_CONSTRUCTOR(displayTest),
        FUNC_CONSTRUCTOR(rippleAdderTest),
        FUNC_CONSTRUCTOR(xorTest),
        FUNC_CONSTRUCTOR(ramTest),
        FUNC_CONSTRUCTOR(memoryProgrammerTest),
        FUNC_CONSTRUCTOR(risingEdgeDetectorTest),
        FUNC_CONSTRUCTOR(upCounter4BitsTest),
        FUNC_CONSTRUCTOR(addressDecoderTest4Bits),
        FUNC_CONSTRUCTOR(register8BitsTest),
        FUNC_CONSTRUCTOR(aluTest),
        FUNC_CONSTRUCTOR(controlUnitTest),
        FUNC_CONSTRUCTOR(addressDecoder8BitsTest),
        FUNC_CONSTRUCTOR(ram256x16Test),
        FUNC_CONSTRUCTOR(register16BitsWithEnableTest),
    };

    uint16_t testNum;
    int optLev;

    if (!DCSLog::checkInputNumber(tests, argc, argv, testNum, optLev))
        return EXIT_FAILURE;

    DCSTimer::initialize("prj", testNum, optLev);
    // start profiled scope
    {
        PROFILE();
        tests[testNum].func();
    }
    DCSLog::printResults();
    DCSTimer::printResults();
    return 0;
}