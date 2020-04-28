#include "DCSLog.hpp"
#include <exception>

class custom_exception : public std::exception {
public:
    int code;
    custom_exception(int code) : code(code) {}

    virtual const char* what() const throw() {
        switch (this->code) {
        case 0:
            return "This function should never be called";
        case 1:
            return "I'm not connected";
        case 2:
            return "Number probe names does not match the number of connections";
        case 3:
            return "Trying to connect output to already connected input\nMultiple connections must "
                   "be tristate";
        case 4:
            return "Trying to connect tristate output to connected input.\nMultiple connections "
                   "must be tristate";
        case 5:
            return "Only 3-state buffers can access this function";
        case 6:
            return "Number of input pins not set";
        case 7:
            return "Number of output pins not set";
        case 8:
            return "Time delay not set";
        case 9:
            return "Number of output pins does not match number of in pins";
        case 10:
            return "Output pin number out of range";
        case 11:
            return "Input pin number out of range";
        case 12:
            return "Trying to access the value in non sequential order";
        case 13:
            return "I don't have a name";
        case 14:
            return "Conflict on the bus among tristate buffers";
        default:
            return "Uncategorized exception";
        }
    }
};

void DCSLog::output(std::string label, std::string message) {
#if LOG_LEVEL > 0
    std::cout << " " << label << ":" << message;
#endif
}

void DCSLog::info(std::string callerName, std::string message) {
#if LOG_LEVEL > 1
    std::cout << "INFO: " << callerName << " says: \"" << message << "\"\n";
#endif
}

void DCSLog::debug(std::string callerName, std::string message) {
#if LOG_LEVEL > 2
    std::cout << "INFO: " << callerName << " says: \"" << message << "\"\n";
#endif
}

void DCSLog::error(std::string callerName, int code) {
    try {
        throw custom_exception(code);
    } catch (custom_exception& e) {
        std::cout << "ERROR: " << callerName << " says: \"" << e.what() << "!\"\n";
        exit(e.code);
    }
}

void DCSLog::printTestName(std::string testName) {
#if LOG_LEVEL > 0
    std::cout << "-----";
    for (size_t i = 0; i < testName.size(); i++)
        std::cout << "-";
    std::cout << "\n" << testName << " test\n";
    for (size_t i = 0; i < testName.size() + 5; i++)
        std::cout << "-";
    std::cout << "\n";
#endif
}
