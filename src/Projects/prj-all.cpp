#include "prj-FastControlUnit.hpp"
#include "prj-fastZeroFlagProgram.hpp"
#include "prj-FirstProgram.hpp"
#include "prj-NoCUComputer.hpp"

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
        if (testNum == N++) firstProgramTest();
        else if (testNum == N++) fastControlUnitTest();
        else if (testNum == N++) fastZeroFlagProgramTest();
        else if (testNum == N++) noCUComputerTest();
        else {
            std::cerr << "Project number exceeding number of last available project (" << N-1 << ")\n";
            return EXIT_FAILURE;
        }
    }
    DCSTimer::printResults();
    DCSLog::printResults();
    return 0;
}