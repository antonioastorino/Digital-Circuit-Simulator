//
//  DCSComponent.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include <vector>
#include <string>
#include <iostream>
#include "DCSWire.hpp"

class DCSComponent {
private:
	
protected:
	~DCSComponent();
	DCSComponent() = delete;
	// Initialize with add=false if the component is not an elementary block
	DCSComponent(int fanIn, int fanOut, bool add=true);
	int fanIn, fanOut;
	uint64_t in = 0;
	uint64_t out = 0;
	// Binary number in which each digit is set = 1 when the corresponding input is updated for the first time.
	uint64_t reachableIn;
	uint64_t allInReached;
	std::vector<DCSWire*> wireVector = {};
	DCSComponent *parent = nullptr;
	
	
public:
	// stores the components to which the output of this component is connected. It is used to propagate signals in series during initialization
	std::vector<DCSComponent*> rightComponentVector = {};
	bool initialized = false;
	bool stable = false;
	virtual void setIn(bool inVal, int inPinNum);
	virtual void setIn(uint64_t inVec);

	bool getOutVal(int outPinNum);
	uint64_t getOutVec();
	
	virtual int getTimeDelay() = 0; // Return the latency between input and output
	virtual void updateOut() = 0;

	virtual void connect(DCSComponent* to,
						 int outPinNum,
						 int inPinNum,
						 std::string probeName = "");
	
	virtual DCSComponent* getLeftComponent(int outPinNum);
	virtual DCSComponent* getRightComponent(int &inPinNum);
	
	void propagateValues();
	void setParent(DCSComponent* parent);
	void updateParentOut();
	
};

#endif /* DCSComponent_hpp */
