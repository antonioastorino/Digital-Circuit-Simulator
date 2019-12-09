//
//  DCSLog.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 09/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSLog_hpp
#define DCSLog_hpp

#include <iostream>

namespace DCSLog {
void info(std::string callerName, std::string message);

void error(std::string callerName, std::string message);
}
#endif /* DCSLog_hpp */
