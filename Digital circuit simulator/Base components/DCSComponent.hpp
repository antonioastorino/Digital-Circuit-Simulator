//
//  DCSComponent.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/* `reachableIn`:
Binary number in which each digit is set = 1 when the corresponding input is updated for the first time.
 `rightComponentVector` stores the components to which the output
of this component is connected.
It is used to propagate signals in sequence during engine initialization.
*/


#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include <vector>
#include <sstream>

class DCSWire;

class DCSComponent {
private:
	DCSComponent();
protected:
	~DCSComponent();
	DCSComponent(std::string name, bool shouldUpdate=true);
	std::string name;
	
	uint64_t in = 0;
	uint64_t out = 0;
	uint64_t reachableIn;
	uint64_t connectedIn;
	uint64_t fromTristateIn;

	std::vector<DCSWire*> wireVector = {};
	bool enabled;
	
public:
	bool isNode;
	bool isTristate;
	
	std::vector<DCSComponent*> rightComponentVector = {};
	bool initialized = false;
	
	virtual void setIn(bool inVal, ushort inPinNum);
	virtual void setIn(uint64_t inVec);
	
	bool getOutVal(ushort outPinNum);
	uint64_t getOutVec();
	
	std::string getName();
	virtual int getTimeDelay() = 0; // Return the latency between input and outpu
	virtual void updateOut() = 0;
	
	void connect(DCSComponent* to,
				 ushort outPinNum,
				 ushort inPinNum,
				 std::string probeName = "");
	
	void connect(DCSComponent* to,
				 DCSPinNumRange outPinNumRange,
				 DCSPinNumRange inPinNumRange,
				 std::vector<std::string> probeNames = {});
	
	void connect(DCSComponent* to,
				 std::vector<std::string> probeNames = {});
	
	virtual DCSComponent* getOutComponent(ushort &outPinNum);
	virtual DCSComponent* getInComponent(ushort &inPinNum);
	
	bool getConnectedIn(ushort inPinNum);
	bool getFromTristateIn(ushort inPinNum);
	void setConnectedIn(ushort inPinNum);
	void setFromTristateIn(ushort inPinNum);
	
	bool isFullyConnected();
	
	bool propagateValues();
	
	virtual ushort getNumOfInPins() = 0;
	virtual ushort getNumOfOutPins() = 0;
	virtual uint64_t getAllReachedQWord();
	
	bool getReachableIn(ushort inPinNum);

	virtual void enable();
	virtual void disable();
	bool getEnabled();
	
};

#endif /* DCSComponent_hpp */
