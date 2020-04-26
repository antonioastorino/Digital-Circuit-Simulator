#ifndef DCSLog_hpp
#define DCSLog_hpp
#define LOG_LEVEL 1
#include <iostream>

class DCSLog {
public:
	static void output(std::string label, std::string message);
	static void info(std::string callerName, std::string message);
	static void debug(std::string callerName, std::string message);
	static void error(std::string callerName, std::string message);
	static void printTestName(std::string testName);
};
#endif /* DCSLog_hpp */
