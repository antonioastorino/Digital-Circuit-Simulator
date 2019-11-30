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
		probeName(probeName) {
			std::cout << from << " out " << outPinNum << " --> " << to << " in " << inPinNum << "\n";
		}
		
		int getOutPinNum() { return outPinNum; }
	};

	
	
	~DCSComponent();
	DCSComponent() = delete;
	// Initialize with add=false if the component is not an elementary block
	DCSComponent(int fanIn, int fanOut, bool add=true);
	int fanIn, fanOut;
	bool *in;
	bool *out;
	
	
public:
	virtual DCSComponent* internalComponetAtInput(int &inPinNumber);
	bool initialized = false;
	bool stable = false;
	std::vector<DCSWire> wireVector = {};
	void setIn(bool inVal, int inPinNum);
	void setIn(bool* inVec);

	bool getOutVal(int outPinNum);
	bool* getOutVal();

	
	virtual void updateOut() = 0;
	void propagateValue();

	virtual void connect(DCSComponent* to,
						 int outPinNum,
						 int inPinNum,
						 std::string probeName = "");
	
};

#endif /* DCSComponent_hpp */
