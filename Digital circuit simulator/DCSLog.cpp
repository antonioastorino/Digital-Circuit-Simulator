//
//  DCSLog.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 09/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSLog.hpp"

void DCSLog::info(std::string callerName, std::string message) {
	std::cout << "INFO: " << callerName << " says '" << message << "'\n";
}

void DCSLog::error(std::string callerName, std::string message) {
	std::cout << "ERROR: " << callerName << " says '" << message << "!'\n";
}
