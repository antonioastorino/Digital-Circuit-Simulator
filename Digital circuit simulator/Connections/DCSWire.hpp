//
//  DCSWire.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSWire_hpp
#define DCSWire_hpp

class DCSComponent;

class DCSWire {
private:
	// Driving component
	DCSComponent* from;
	// output pin number of the output component
	ushort outPinNum;
	// Drived component
	DCSComponent* to;
	// input pin number of the driven component
	ushort inPinNum;
	std::string probeName;
	
public:
	DCSWire() = delete;
	DCSWire(DCSComponent* from,
			ushort outPinNum,
			DCSComponent* to,
			ushort inPinNum,
			std::string probeName = "");
	
	ushort getOutPinNum();
	std::string getProbeName();
	bool propagateValue();
	bool getOutVal();
};



#endif /* DCSWire_hpp */
