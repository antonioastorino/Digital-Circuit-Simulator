#ifndef DCSRippleAdder8Bits_hpp
#define DCSRippleAdder8Bits_hpp
#include "DCSComponentArray.hpp"
class DCSFullAdder;

class DCSRippleAdder8Bits: public DCSComponent {
private:
	DCSComponentArray<DCSFullAdder> faArray;
public:
	DCSRippleAdder8Bits(std::string name);

	DCSComponent* getInComponent(unsigned short &inPinNum) override;
	DCSComponent* getOutComponent(unsigned short &outPinNum) override;
	
	void updateOut() override;
};

#endif /* DCSRippleAdder8Bits_hpp */
