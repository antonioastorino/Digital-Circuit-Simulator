//
//  DCSLog.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 09/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSLog_hpp
#define DCSLog_hpp

class DCSLog {
public:
	static bool verbose;
	
	static void info(std::string callerName, std::string message);
	
	static void error(std::string callerName, std::string message);
	
};
#endif /* DCSLog_hpp */
