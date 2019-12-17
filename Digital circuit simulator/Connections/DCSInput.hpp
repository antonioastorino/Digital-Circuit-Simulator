//
//  DCSInput.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//
/*
 Use this gate to initialize the input values.
 These gates are not optional as they set the beginning of the propagation
 */

#ifndef DCSInput_hpp
#define DCSInput_hpp


class DCSInput: public DCSComponent {
private:
	bool hasSignal = false;
	bool constValue = 0;
	DCSArbitrarySignal *signal;
public:
	DCSInput(std::string name);
	DCSInput(std::string name, bool initValue);
	DCSInput(std::string name, binary_signal signal, bool synch = false);
	~DCSInput();
	
	void makeSignal(bool constValue);
	void makeSignal(binary_signal signal, bool synch=false);
	void makeClock();
	void updateOut() override;
	
	ushort getNumOfInPins() override { return 0; };
	ushort getNumOfOutPins() override { return 1; };

	int getTimeDelay() override { return 1; };
};

#endif /* DCSInput_hpp */
