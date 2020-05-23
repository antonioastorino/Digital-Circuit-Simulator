#ifndef DCSLog_hpp
#define DCSLog_hpp
#define LOG_LEVEL 1
#include <iostream>
#include <sstream>

class DCSLog {
public:
    static std::stringstream outStream;
    static void output(std::string label, std::string message);
    static void info(std::string callerName, std::string message);
    static void debug(std::string callerName, std::string message);
    static void error(std::string callerName, int code);
    
    static void printTestName(std::string testName);
    static void printProjectName(std::string testName);
    static void printResults();
};
#endif /* DCSLog_hpp */
