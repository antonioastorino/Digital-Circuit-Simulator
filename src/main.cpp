void srLatchTest();
void notLoopTest();
void unitDelayTest();
void risingEdgeDetectorTest();
void dFlipFlopTest();
void triStateBufferTest();
void andArrayTest();
void orTest();
void nor3Test();
void nand3Test();
void and6Test();
void dLatchTest();
void dLatchAsyncSRTest();
void jkLatchMasterSlaveAsyncSRTest();
void register1BitTest();
void dividerTest();
void upCounterTest();
void register8BitsTest();
void countAndStoreTest();
void mux2To1Test();
void fullAdderTest();
void bitStreamSignalTest();
void displayTest();
void rippleAdderTest();
void ramProgrammerTest();
void firstProgramTest();
void ramTest();
void demoTest();
void upCounter4BitsTest();
void addressDecoderTest();

#include <iostream>
#include "DCSTimer.hpp"

int main(int argc, const char* argv[]) {
    // TODO: create proper unit tests
    int testNum = -1;
	if (argc == 2) {
    	sscanf(argv[1], "%d", &testNum);
	}
    switch (testNum) {
    case (0):
        bitStreamSignalTest();
        break;
    case (1):
        orTest();
        break;
    case (2):
        unitDelayTest();
        break;
    case (3):
        nor3Test();
        break;
    case (4):
        notLoopTest();
        break;
    case (5):
        nand3Test();
        break;
    case (6):
        andArrayTest();
        break;
    case (7):
        and6Test();
        break;
    case (8):
        srLatchTest();
        break;
    case (9):
        triStateBufferTest();
        break;
    case (10):
        dLatchTest();
        break;
    case (11):
        dLatchAsyncSRTest();
        break;
    case (12):
        dFlipFlopTest();
        break;
    case (13):
        register1BitTest();
        break;
    case (14):
        register8BitsTest();
        break;
    case (15):
        jkLatchMasterSlaveAsyncSRTest();
        break;
    case (16):
        dividerTest();
        break;
    case (17):
        upCounterTest();
        break;
    case (18):
        mux2To1Test();
        break;
    case (19):
        fullAdderTest();
        break;
    case (20):
        displayTest();
        break;
    case (21):
        rippleAdderTest();
        break;
    case (22):
        countAndStoreTest();
        break;
    case (23):
        ramTest();
        break;
    case (24):
        firstProgramTest();
        break;
    case (25):
        // ramProgrammerTest();
        break;
    case (26):
        risingEdgeDetectorTest();
        break;
    case (27):
        upCounter4BitsTest();
        break;
    case (28):
        addressDecoderTest();
        break;
    default:
		demoTest();
        break;
    }
    DCSTimer::printResults();
    return 0;
}