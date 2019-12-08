//
//  DCSWire.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSWire_hpp
#define DCSWire_hpp

#include <string>
#include <iostream>

class DCSComponent;

class DCSWire {
private:
	// Driving component
	DCSComponent* from;
	// output pin number of the output component
	int outPinNum;
	// Drived component
	DCSComponent* to;
	// input pin number of the driven component
	int inPinNum;
	std::string probeName;
	
public:
	DCSWire() = delete;
	DCSWire(DCSComponent* from,
			int outPinNum,
			DCSComponent* to,
			int inPinNum,
			std::string probeName = "")
	:
	from(from),
	outPinNum(outPinNum),
	to(to),
	inPinNum(inPinNum),
	probeName(probeName) {
		std::cout << from << " out " << outPinNum << " --> " << to << " in " << inPinNum << "\n";
	}
	
	int getOutPinNum();
	std::string getProbeName();
	void propagateValue();
	bool getOutVal();
};



#endif /* DCSWire_hpp */
