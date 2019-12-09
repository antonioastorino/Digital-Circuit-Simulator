//
//  DCSLog.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 09/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSLog_h
#define DCSLog_h

#include <iostream>

namespace DCSLog {

bool verbose = false;

void info(std::string callerName, std::string message) {
	if (verbose) {
		std::cout << "INFO: " << callerName << " says '" << message << "'\n";
	}
}

void error(std::string callerName, std::string message) {
	std::cout << "ERROR: " << callerName << " says '" << message << "!'\n";
}
}

#endif /* DCSLog_h */
