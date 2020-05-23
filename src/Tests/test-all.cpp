#include "DCSLog.hpp"
#include "DCSTimer.hpp"
#include "test-ALU.hpp"
#include "test-AddressDecoder.hpp"
#include "test-AddressDecoder32Bits.hpp"
#include "test-And6.hpp"
#include "test-AndArray.hpp"
#include "test-BitStreamSignal.hpp"
#include "test-ControlUnit.hpp"
#include "test-DFlipFlop.hpp"
#include "test-DLatch.hpp"
#include "test-DLatchAsyncSR.hpp"
#include "test-Display.hpp"
#include "test-Divider.hpp"
#include "test-FullAdder.hpp"
#include "test-JKMasterSlave.hpp"
#include "test-MemoryProgrammer.hpp"
#include "test-Mux2To1.hpp"
#include "test-Nand3.hpp"
#include "test-Nor3.hpp"
#include "test-NotLoop.hpp"
#include "test-Or.hpp"
#include "test-Ram.hpp"
#include "test-Ram256x16.hpp"
#include "test-Register16BitsWithEnable.hpp"
#include "test-Register1Bit.hpp"
#include "test-Register1BitWithEnable.hpp"
#include "test-Register8Bits.hpp"
#include "test-Register8BitsWithEnable.hpp"
#include "test-RippleAdder.hpp"
#include "test-RisingEdgeDetector.hpp"
#include "test-SRLatch.hpp"
#include "test-TriStateBuffer.hpp"
#include "test-UnitDelay.hpp"
#include "test-UpCounter.hpp"
#include "test-UpCounter4Bits.hpp"
#include "test-Xor.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    // TODO: create proper unit tests
    int testNum = 0;
    if (argc == 2) {
        sscanf(argv[1], "%d", &testNum);
    }
    DCSTimer::initialize(testNum);
    {
        uint16_t N = 0;
        PROFILE();
        if (testNum == N++) bitStreamSignalTest();
        else if (testNum == N++) orTest();
        else if (testNum == N++) unitDelayTest();
        else if (testNum == N++) nor3Test();
        else if (testNum == N++) notLoopTest();
        else if (testNum == N++) nand3Test();
        else if (testNum == N++) andArrayTest();
        else if (testNum == N++) and6Test();
        else if (testNum == N++) srLatchTest();
        else if (testNum == N++) triStateBufferTest();
        else if (testNum == N++) dLatchTest();
        else if (testNum == N++) dLatchAsyncSRTest();
        else if (testNum == N++) dFlipFlopTest();
        else if (testNum == N++) register1BitWithEnableTest();
        else if (testNum == N++) register8BitsWithEnableTest();
        else if (testNum == N++) jkLatchMasterSlaveAsyncSRTest();
        else if (testNum == N++) dividerTest();
        else if (testNum == N++) upCounterTest();
        else if (testNum == N++) mux2To1Test();
        else if (testNum == N++) fullAdderTest();
        else if (testNum == N++) displayTest();
        else if (testNum == N++) rippleAdderTest();
        else if (testNum == N++) xorTest();
        else if (testNum == N++) ramTest();
        else if (testNum == N++) memoryProgrammerTest();
        else if (testNum == N++) risingEdgeDetectorTest();
        else if (testNum == N++) upCounter4BitsTest();
        else if (testNum == N++) addressDecoderTest();
        else if (testNum == N++) register8BitsTest();
        else if (testNum == N++) aluTest();
        else if (testNum == N++) controlUnitTest();
        else if (testNum == N++) addressDecoder32BitsTest();
        else if (testNum == N++) ram256x16Test();
        else if (testNum == N++) register16BitsWithEnableTest();
        else {
            std::cerr << "Test number exceeding number of last available test (" << N-1 << ")\n";
            return EXIT_FAILURE;
        }
    }
    DCSTimer::printResults();
    DCSLog::printResults();
    return 0;
}