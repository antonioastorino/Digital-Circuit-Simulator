//
//  DCSComponentArray.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSComponentArray_hpp
#define DCSComponentArray_hpp

#include <vector>
#include "DCSAnd.hpp"
#include "DCSOr.hpp"
#include "DCSNot.hpp"
#include "DCSNor.hpp"
#include "DCSNor3.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSSRLatch.hpp"
#include "DCSOutput.hpp"
#include "DCSDLatch.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSTriStateBuffer.hpp"

template<class T>
class DCSComponentArray: public DCSComponent {
private:
	std::vector<T*> componentArray;
	std::string name;
	ushort numOfElements;
public:
	DCSComponentArray(std::string name, ushort numOfElements);
	~DCSComponentArray();
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	
	ushort getNumOfInPins() override { return componentArray[0]->getNumOfInPins() * numOfElements; };
	ushort getNumOfOutPins() override { return componentArray[0]->getNumOfOutPins() * numOfElements; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
	T* operator [] (ushort  elemNum);
};




#endif /* DCSComponentArray_hpp */
