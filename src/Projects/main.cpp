#include <iostream>
#include <vector>

#include "DCSLog.hpp"

#include "prj-FastControlUnit.hpp"
#include "prj-countByThrees.hpp"
#include "prj-NoCUComputer.hpp"
#include "prj-fastZeroFlagProgram.hpp"

int main(int argc, const char* argv[]) {

    std::vector<func_descriptor> projects = {
        FUNC_CONSTRUCTOR(countByThrees),
        FUNC_CONSTRUCTOR(fastControlUnitPrj),
        FUNC_CONSTRUCTOR(fastZeroFlagProgramPrj),
        FUNC_CONSTRUCTOR(noCUComputerPrj),
    };

    uint16_t prjNum;
    int optLev;

    if (!DCSLog::checkInputNumber(projects, argc, argv, prjNum, optLev)) {
        return EXIT_FAILURE;
    }

    DCSTimer::initialize("prj", prjNum, optLev);
    // start profiled scope
    {
        PROFILE();
        projects[prjNum].func();
    }
    DCSLog::printResults();
    DCSTimer::printResults();
    return 0;
}