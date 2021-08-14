#include "DCSLog.hpp"
#include "DCSTimer.hpp"
#include <exception>

std::stringstream DCSLog::outStream;

class custom_exception : public std::exception
{
public:
    int code;
    custom_exception(int code) : code(code) {}

    virtual const char* what() const throw()
    {
        switch (this->code)
        {
        case 0:
            return "This function should never be called";
        case 1:
            return "I'm not connected";
        case 2:
            return "Number probe names does not match the number of connections";
        case 3:
            return "Trying to connect output to already connected input\n"
                   "Multiple connections must be tristate";
        case 4:
            return "Trying to connect tristate output to connected input.\n"
                   "Multiple connections must be tristate";
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
        case 15:
            return "Timer already initialized";
        case 16:
            return "Exceeded maximum number of bits (32)";
        case 17:
            return "RAM not ready. Have you called useRamElements() after programming the RAM?";
        case 18:
            return "Engine not initialized";
        case 19:
            return "Engine already initialized";
        case 20:
            return "Timer already initialized";
        case 21:
            return "Optimization level outside the allowed range [0, 3]";
        default:
            return "Uncategorized exception";
        }
    }
};

void DCSLog::output(std::string label, std::string message)
{
#if LOG_LEVEL > 0
    DCSLog::outStream << " " << label << ":" << message;
#endif
}

void DCSLog::info(std::string callerName, std::string message)
{
#if LOG_LEVEL > 1
    DCSLog::outStream << "INFO: " << callerName << " says: \"" << message << "\"\n";
#endif
}

void DCSLog::debug(std::string callerName, std::string message)
{
#if LOG_LEVEL > 2
    DCSLog::outStream << "INFO: " << callerName << " says: \"" << message << "\"\n";
#endif
}

void DCSLog::error(std::string callerName, int code)
{
    try
    {
        throw custom_exception(code);
    }
    catch (custom_exception& e)
    {
        DCSLog::outStream << "ERROR: " << callerName << " says: \"" << e.what() << "!\"\n";
        DCSLog::printResults(); // Print what you have before throwing an error
        DCSTimer::printResults();
        exit(e.code);
    }
}

bool DCSLog::checkInputNumber(std::vector<func_descriptor> funcs, int argc, const char** argv,
                              uint16_t& num, int& optLev)
{
    // check that a test or project number is passed as parameter
    if (argc < 2)
    {
        std::cerr << "\nPlease add a valid project or test number as a parameter.\nChoose one of "
                     "the following:\n#\tTitle\n";
        for (size_t i = 0; i < funcs.size(); i++)
        {
            std::cerr << i << "\t" << funcs[i].func_name << "\n";
        }
        return false;
    }
    // check that there are no paramters in excess
    if (argc > 2)
        return false;

    // get the paramter value
    sscanf(argv[1], "%hd", &num);
    // check that it is a valid value
    if (num >= funcs.size())
    {
        std::cerr << "Project or test number too high (max " << funcs.size() - 1 << ")\n";
        for (size_t i = 0; i < funcs.size(); i++)
        {
            std::cerr << i << "\t" << funcs[i].func_name << "\n";
        }
        return false;
    }
    // Retrieve optimization level from the file name
    int i = 0;
    while (argv[0][i] != '\0')
        i++;                                             // count chars in file name
    optLev = static_cast<uint16_t>(argv[0][i - 1]) - 48; // convert the last char into an int
    if (optLev < 0 || optLev > 3)
        DCSLog::error("main", 20); // check it's between 0 and 3

    return true;
}

void DCSLog::printTestName(std::string testName)
{
#if LOG_LEVEL > 0
    DCSLog::outStream << "-----";
    for (size_t i = 0; i < testName.size(); i++)
        DCSLog::outStream << "-";
    DCSLog::outStream << "\n" << testName << " test\n";
    for (size_t i = 0; i < testName.size() + 5; i++)
        DCSLog::outStream << "-";
    DCSTimer::title = testName + " test";
    DCSLog::outStream << "\n";
#endif
}

void DCSLog::printProjectName(std::string prjName)
{
#if LOG_LEVEL > 0
    DCSLog::outStream << "--------";
    for (size_t i = 0; i < prjName.size(); i++)
        DCSLog::outStream << "-";
    DCSLog::outStream << "\n" << prjName << " project\n";
    for (size_t i = 0; i < prjName.size() + 8; i++)
        DCSLog::outStream << "-";
    DCSLog::outStream << "\n";
    DCSTimer::title = prjName + " project";
#endif
}

void DCSLog::printResults()
{
#if LOG_LEVEL > 0
    std::cout << DCSLog::outStream.str();
#endif
}
