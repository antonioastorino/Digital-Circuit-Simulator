//
//  DCSAnd6.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSAnd6_hpp
#define DCSAnd6_hpp

class DCSAnd6: public DCSComponent {
private:
	DCSComponentArray<DCSAnd3> and3array;
	DCSAnd and0;
public:
	DCSAnd6(std::string name);

	DCSComponent* getInComponent(ushort &inPinNum) override;
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	
	ushort getNumOfInPins() override {return 6; };
	ushort getNumOfOutPins() override {return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 2; };
};

#endif /* DCSAnd6_hpp */
