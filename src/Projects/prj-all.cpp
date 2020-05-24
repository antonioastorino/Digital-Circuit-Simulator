#include <iostream>

#include "prj-FastControlUnit.hpp"
#include "prj-FirstProgram.hpp"
#include "prj-NoCUComputer.hpp"
#include "prj-fastZeroFlagProgram.hpp"

int main(int argc, const char* argv[]) {
    // Retrieve optimization level from the file name
    int i = 0;
    while (argv[0][i] != '\0') i++;                          // count chars in file name
    int optLev = static_cast<uint16_t>(argv[0][i - 1]) - 48; // convert the last char into an int
    if (optLev < 0 && optLev > 3) DCSLog::error("main", 40); // check it's between 0 and 3

    uint16_t prjNum = 0;
    if (argc >= 2) sscanf(argv[1], "%hd", &prjNum);

    DCSTimer::initialize("prj", prjNum, optLev);
    // start profiled scope
    {
        uint16_t N = 0;
        PROFILE();
        if (prjNum == N++) firstProgramPrj();
        if (prjNum == N++) fastControlUnitPrj();
        if (prjNum == N++) fastZeroFlagProgramPrj();
        if (prjNum == N++) noCUComputerPrj();
        if (prjNum >= N) {
            std::cerr << "Project number exceeding number of last available project (" << N - 1
                      << ")\n";
            return EXIT_FAILURE;
        }
    }
    DCSLog::printResults();
    DCSTimer::printResults();
    return 0;
}