#ifndef DCSHeader_h
#define DCSHeader_h

#define LOG_LEVEL 1

#include <sstream>
#include <iostream>
#include <vector>

#ifndef ushort
	typedef unsigned short ushort;
#endif

typedef std::vector<uint64_t> binary_signal;

void printTestName(std::string testName);

#endif /* DCSHeader_h */
