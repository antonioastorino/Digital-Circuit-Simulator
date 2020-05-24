#include <iostream>

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

int main(int argc, const char* argv[]) {
    // Retrieve optimization level from the file name
    int i = 0;
    while (argv[0][i] != '\0') i++;                          // count chars in file name
    int optLev = static_cast<uint16_t>(argv[0][i - 1]) - 48; // convert the last char into an int
    if (optLev < 0 && optLev > 3) DCSLog::error("main", 40); // check it's between 0 and 3

    uint16_t testNum = 0;
    if (argc >= 2) sscanf(argv[1], "%hd", &testNum);

    DCSTimer::initialize("test", testNum, optLev);
    // start profiled scope
    {
        uint16_t N = 0;
        PROFILE();
        if (testNum == N++) bitStreamSignalTest();
        if (testNum == N++) orTest();
        if (testNum == N++) unitDelayTest();
        if (testNum == N++) nor3Test();
        if (testNum == N++) notLoopTest();
        if (testNum == N++) nand3Test();
        if (testNum == N++) andArrayTest();
        if (testNum == N++) and6Test();
        if (testNum == N++) srLatchTest();
        if (testNum == N++) triStateBufferTest();
        if (testNum == N++) dLatchTest();
        if (testNum == N++) dLatchAsyncSRTest();
        if (testNum == N++) dFlipFlopTest();
        if (testNum == N++) register1BitWithEnableTest();
        if (testNum == N++) register8BitsWithEnableTest();
        if (testNum == N++) jkLatchMasterSlaveAsyncSRTest();
        if (testNum == N++) dividerTest();
        if (testNum == N++) upCounterTest();
        if (testNum == N++) mux2To1Test();
        if (testNum == N++) fullAdderTest();
        if (testNum == N++) displayTest();
        if (testNum == N++) rippleAdderTest();
        if (testNum == N++) xorTest();
        if (testNum == N++) ramTest();
        if (testNum == N++) memoryProgrammerTest();
        if (testNum == N++) risingEdgeDetectorTest();
        if (testNum == N++) upCounter4BitsTest();
        if (testNum == N++) addressDecoderTest();
        if (testNum == N++) register8BitsTest();
        if (testNum == N++) aluTest();
        if (testNum == N++) controlUnitTest();
        if (testNum == N++) addressDecoder32BitsTest();
        if (testNum == N++) ram256x16Test();
        if (testNum == N++) register16BitsWithEnableTest();
        if (testNum >= N) {
            std::cerr << "Test number exceeding number of last available test (" << N - 1 << ")\n";
            return EXIT_FAILURE;
        }
    }

    DCSLog::printResults();
    DCSTimer::printResults();
    return 0;
}