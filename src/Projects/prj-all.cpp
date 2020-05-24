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
        if (prjNum == N++) firstProgramPrj();
        else if (prjNum == N++) fastControlUnitPrj();
        else if (prjNum == N++) fastZeroFlagProgramPrj();
        else if (prjNum == N++) noCUComputerPrj();
        else {
            std::cerr << "Project number exceeding number of last available project (" << N-1 << ")\n";
            return EXIT_FAILURE;
        }
    }
    DCSLog::printResults();
    DCSTimer::printResults();
    return 0;
}