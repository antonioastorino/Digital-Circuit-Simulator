//
//  DCSMux2to1.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 20/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSMux2to1_hpp
#define DCSMux2to1_hpp

class DCSMux2to1: public DCSComponent {
private:
	DCSAnd and0;
	DCSAnd and1;
	DCSNot not0;
	DCSUnitDelay del0;
	DCSOr or0;
	DCSNode node0;
public:
	DCSMux2to1(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 3; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 2; };
};

#endif /* DCSMux2to1_hpp */
