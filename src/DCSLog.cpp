//
//  DCSLog.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 09/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSLog.hpp"

void DCSLog::output(std::string label, std::string message) {
#if LOG_LEVEL>0
		std::cout << " " << label << ":" << message;
#endif
}

void DCSLog::info(std::string callerName, std::string message) {
#if LOG_LEVEL>1
	std::cout << "INFO: " << callerName << " says: '" << message << "'\n";
#endif
}

void DCSLog::debug(std::string callerName, std::string message) {
#if LOG_LEVEL>2
	std::cout << "INFO: " << callerName << " says: '" << message << "'\n";
#endif
}


void DCSLog::error(std::string callerName, std::string message) {
	std::cout << "ERROR: " << callerName << " says: '" << message << "!'\n";
	throw "ERROR";
}

