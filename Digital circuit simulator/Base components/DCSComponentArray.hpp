//
//  DCSComponentArray.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSComponentArray_hpp
#define DCSComponentArray_hpp

class DCSComponent;

template<class T>
class DCSComponentArray: public DCSComponent {
private:
	std::vector<T*> componentArray;
	std::string name;
	ushort numOfElements;

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
