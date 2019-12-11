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
#include "DCSLog.hpp"
#include <vector>

class DCSComponent {
private:
	
protected:
	~DCSComponent();
	DCSComponent() = delete;
	// Initialize with add=false if the component is not an elementary block
	DCSComponent(std::string name, int fanIn, int fanOut, bool add=true);
	std::string name;
	int fanIn, fanOut;
	uint64_t in = 0;
	uint64_t out = 0;
	/* `reachableIn`:
	 Binary number in which each digit is set = 1 when the corresponding input is updated for the first time.
	 */
	uint64_t reachableIn;
	uint64_t allInReached;
	
	uint64_t connectedIn;
	uint64_t fromTristateIn;

	std::vector<DCSWire*> wireVector = {};
	DCSComponent *parent = nullptr;
	
public:
	bool isNode;
	bool isTristate;
	/* `rightComponentVector` stores the components to which the output
	 of this component is connected.
	 It is used to propagate signals in sequence during engine initialization.
	 */
	std::vector<DCSComponent*> rightComponentVector = {};
	bool initialized = false;
	virtual void setIn(bool inVal, int inPinNum);
	virtual void setIn(uint64_t inVec);
	
	bool getOutVal(int outPinNum);
	uint64_t getOutVec();
	
	std::string getName();
	
	virtual int getTimeDelay() = 0; // Return the latency between input and output
	virtual void updateOut() = 0;
	
	virtual void connect(DCSComponent* to,
						 int outPinNum,
						 int inPinNum,
						 std::string probeName = "");
	
	virtual DCSComponent* getOutComponent(int &outPinNum);
	virtual DCSComponent* getInComponent(int &inPinNum);
	
	/* Sets the state of a given input pin.
	 If this pin has already been connected it returns false, otherwise true.
	 */
	bool getConnectedIn(int inPinNum);
	bool getFromTristateIn(int inPinNum);
	void setConnectedIn(int inPinNum);
	void setFromTristateIn(int inPinNum);
	
	bool isFullyConnected();
	
	void propagateValues();
	/* A parent is a component whose output is shared with this component.
	 Every time the output of this component is updated, also the parent's output will.
	 See `updateOut()` and `updatedParentOut()`.
	 */
	void setParent(DCSComponent* parent);
	void updateParentOut();
	
};

#endif /* DCSComponent_hpp */
