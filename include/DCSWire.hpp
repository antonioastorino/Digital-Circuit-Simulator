#ifndef DCSWire_hpp
#define DCSWire_hpp
#include "DCSComponent.hpp"

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
