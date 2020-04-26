#ifndef DCSAddressDecoder4Bits_hpp
#define DCSAddressDecoder4Bits_hpp
#include "DCSComponentArray.hpp"
class DCSNode;
class DCSUnitDelay;
class DCSNot;
class DCSAnd4;

class DCSAddressDecoder4Bits: public DCSComponent {
private:
	DCSComponentArray<DCSNode> nodeArray;
	DCSComponentArray<DCSNot> notArray;
	DCSComponentArray<DCSUnitDelay> delArray;
	DCSComponentArray<DCSAnd4> and4Array;
public:
	DCSAddressDecoder4Bits(std::string name);
	
	DCSComponent* getOutComponent(unsigned short &outPinNum) override;
	DCSComponent* getInComponent(unsigned short &inPinNum) override;
	void updateOut() override;
};

#endif /* DCSAddressDecoder4Bits_hpp */