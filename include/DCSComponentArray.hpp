#ifndef DCSComponentArray_hpp
#define DCSComponentArray_hpp
#include "DCSComponent.hpp"

/** 
 * @class DCSComponentArray
 * Generates an array of identical components.
*/
template<class T>
class DCSComponentArray: public DCSComponent {
private:
	unsigned short numOfElements;
	std::string name;
	std::vector<T*> componentArray;

	void initialize();

public:
	DCSComponentArray(std::string name, unsigned short numOfElements);
	DCSComponentArray(std::vector<std::string> nameVector, unsigned short numOfElements);
	~DCSComponentArray();
	
	DCSComponent* getOutComponent(unsigned short &outPinNum) override;
	DCSComponent* getInComponent(unsigned short &inPinNum) override;
	
	void updateOut() override;
	T* operator [] (unsigned short  elemNum);
};

#endif /* DCSComponentArray_hpp */
