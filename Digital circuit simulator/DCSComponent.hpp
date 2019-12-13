//
//  DCSComponent.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include "DCSWire.hpp"
#include <vector>

class DCSComponent {
private:
	DCSComponent();
protected:
	~DCSComponent();
	// Initialize with add=false if the component is not an elementary block
	DCSComponent(std::string name, bool add=true);
	std::string name;
	
	uint64_t in = 0;
	uint64_t out = 0;
	
	/* `reachableIn`:
	 Binary number in which each digit is set = 1 when the corresponding input is updated for the first time.
	 */
	uint64_t reachableIn;
	
	uint64_t connectedIn;
	uint64_t fromTristateIn;

	std::vector<DCSWire*> wireVector = {};
//	DCSComponent *parent = nullptr;
	bool enabled;
	
public:
	bool isNode;
	bool isTristate;
	/* `rightComponentVector` stores the components to which the output
	 of this component is connected.
	 It is used to propagate signals in sequence during engine initialization.
	 */
	std::vector<DCSComponent*> rightComponentVector = {};
	bool initialized = false;
	virtual void setIn(bool inVal, ushort inPinNum);
	virtual void setIn(uint64_t inVec);
	
	bool getOutVal(ushort outPinNum);
	uint64_t getOutVec();
	
	std::string getName();
	
	virtual int getTimeDelay() = 0; // Return the latency between input and output
	virtual void updateOut() = 0;
	
	virtual void connect(DCSComponent* to,
						 ushort outPinNum,
						 ushort inPinNum,
						 std::string probeName = "");
	
	virtual DCSComponent* getOutComponent(ushort &outPinNum);
	virtual DCSComponent* getInComponent(ushort &inPinNum);
	
	/* Sets the state of a given input pin.
	 If this pin has already been connected it returns false, otherwise true.
	 */
	bool getConnectedIn(ushort inPinNum);
	bool getFromTristateIn(ushort inPinNum);
	void setConnectedIn(ushort inPinNum);
	void setFromTristateIn(ushort inPinNum);
	
	bool isFullyConnected();
	
	void propagateValues();
//	/* A parent is a component whose output is shared with this component.
//	 Every time the output of this component is updated, also the parent's output will.
//	 See `updateOut()` and `updatedParentOut()`.
//	 */
//	void setParent(DCSComponent* parent);
//	void updateParentOut();
	
	virtual ushort getNumOfInPins() = 0;
	virtual ushort getNumOfOutPins() = 0;
	virtual uint64_t getAllReachedQWord();

	virtual void enable();
	virtual void disable();
	bool getEnabled();
	
};

#endif /* DCSComponent_hpp */
