//
//  DCSWire.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSWire_hpp
#define DCSWire_hpp

/// Represents a link between one output pin of one component (`from`) and one pin of another component (`to`)
class DCSWire {
private:
	// Driving component
	DCSComponent* from;
	// Driven component
	DCSComponent* to;
	// input pin number of the `right` component
	ushort inPinNum;
	std::string probeName;
	
public:
	DCSWire() = delete;
	DCSWire(DCSComponent* from,
			DCSComponent* to,
			ushort inPinNum,
			std::string probeName = "");

	std::string getProbeName();
	bool propagateValue();
	bool getOutVal();
};



#endif /* DCSWire_hpp */
