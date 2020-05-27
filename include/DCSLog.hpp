#ifndef DCSLog_hpp
#define DCSLog_hpp
#define LOG_LEVEL 1
#define FUNC_CONSTRUCTOR(func)                                                                     \
    { func, #func }
#include <iostream>
#include <sstream>
#include <vector>

typedef struct {
    void (*func)();
    const char* func_name;
} func_descriptor;

class DCSLog {
private:
public:
    static std::stringstream outStream;
    static void output(std::string label, std::string message);
    static void info(std::string callerName, std::string message);
    static void debug(std::string callerName, std::string message);
    static void error(std::string callerName, int code);

    static bool checkInputNumber(std::vector<func_descriptor>, int, const char**, uint16_t&, int&);
    static void printTestName(std::string testName);
    static void printProjectName(std::string testName);
    static void printResults();
};
#endif /* DCSLog_hpp */
