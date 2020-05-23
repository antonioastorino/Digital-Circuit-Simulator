#include "prj-FastControlUnit.hpp"
#include "prj-fastZeroFlagProgram.hpp"
#include "prj-FirstProgram.hpp"
#include "prj-NoCUComputer.hpp"

#include <iostream>

int main(int argc, const char* argv[]) {
    // TODO: create proper unit tests
    uint16_t prjNum = 0;
    if (argc == 2) {
        sscanf(argv[1], "%hd", &prjNum);
    }
    DCSTimer::initialize("prj", prjNum);
    {
        uint16_t N = 0;
        PROFILE();
        if (prjNum == N++) firstProgramTest();
        else if (prjNum == N++) fastControlUnitTest();
        else if (prjNum == N++) fastZeroFlagProgramTest();
        else if (prjNum == N++) noCUComputerTest();
        else {
            std::cerr << "Project number exceeding number of last available project (" << N-1 << ")\n";
            return EXIT_FAILURE;
        }
    }
    DCSLog::printResults();
    DCSTimer::printResults();
    return 0;
}