//
//  DCSComponentArray.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSComponentArray_hpp
#define DCSComponentArray_hpp
#include "DCSComponent.hpp"

template<class T>
/// Array of components
class DCSComponentArray: public DCSComponent {
private:
	ushort numOfElements;
	std::string name;
	std::vector<T*> componentArray;

	void initialize();

public:
	DCSComponentArray(std::string name, ushort numOfElements);
	DCSComponentArray(std::vector<std::string> nameVector, ushort numOfElements);
	~DCSComponentArray();
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	
	void updateOut() override;
	T* operator [] (ushort  elemNum);
};




#endif /* DCSComponentArray_hpp */
