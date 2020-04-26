#include "DCSLog.hpp"

void DCSLog::output(std::string label, std::string message) {
#if LOG_LEVEL > 0
    std::cout << " " << label << ":" << message;
#endif
}

void DCSLog::info(std::string callerName, std::string message) {
#if LOG_LEVEL > 1
    std::cout << "INFO: " << callerName << " says: '" << message << "'\n";
#endif
}

void DCSLog::debug(std::string callerName, std::string message) {
#if LOG_LEVEL > 2
    std::cout << "INFO: " << callerName << " says: '" << message << "'\n";
#endif
}

void DCSLog::error(std::string callerName, std::string message) {
    std::cout << "ERROR: " << callerName << " says: '" << message << "!'\n";
    throw "ERROR";
}

void DCSLog::printTestName(std::string testName) {
#if LOG_LEVEL > 0
    std::cout << "\n-----";
    for (size_t i = 0; i < testName.size(); i++)
        std::cout << "-";
    std::cout << "\n" << testName << " test\n";
    for (size_t i = 0; i < testName.size() + 5; i++)
        std::cout << "-";
    std::cout << "\n";
#endif
}
