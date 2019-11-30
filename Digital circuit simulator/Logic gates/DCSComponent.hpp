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

class DCSComponent {
protected:
	
	struct DCSWire {
	public:
		// Drived component
		DCSComponent* to;
		// output pin number of the output component
		int outPinNum;
		// input pin number of the driven component
		int inPinNum;
		std::string probeName;
		DCSWire() = delete;
		DCSWire(DCSComponent* from,
				int outPinNum,
				DCSComponent* to,
				int inPinNum,
				std::string probeName = "")
		:
		outPinNum(outPinNum),
		to(to),
		inPinNum(inPinNum),
		probeName(probeName) {}
		
		int getOutPinNum() { return outPinNum; }
	};

	
	~DCSComponent();
	DCSComponent() = delete;
	DCSComponent(int fanIn, int fanOut);
	int fanIn, fanOut;
	bool *in;
	bool *out;
	std::vector<DCSComponent*> connectedComponentVector = {};



public:
	bool initialized = false;
	bool stable = false;
	std::vector<DCSWire> wireVector = {};
	void setIn(bool inVal, int inPinNum);
	void setIn(bool* inVal);

	bool getOutVal(int outPinNum);
	bool* getOutVal();

	
	virtual void updateOut() = 0;
	void propagateValue();

	void connect(DCSComponent* to,
				 int outPinNum,
				 int inPinNum,
				 std::string probeName = "");
	
	std::vector<DCSComponent*> getConnectedComponentVector();
};

#endif /* DCSComponent_hpp */
