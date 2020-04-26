#ifndef DCSDisplayNBits_hpp
#define DCSDisplayNBits_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSDisplayNBits
 * 
 *
*/
class DCSDisplayNBits: public DCSComponent {
private:
	unsigned short numOfBits;
	unsigned short numOfDecimalDigits;
public:
	DCSDisplayNBits(std::string name, unsigned short numOfBits);
	void updateOut() override;
};

#endif /* DCSDisplayNBits_hpp */
