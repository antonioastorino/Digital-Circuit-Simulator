/*

 Input 0: Output Enable
 Input 1: Clock
 Input 2: Clear
 Input 3: Preset
 Input 4: Load
 Input 5: In bit 0
 Input 6: In bit 1
 ...
 
 Out   0: Out bit 0
 Out   1: Out bit 1
 ...
 */                         

#ifndef DCSRegister8Bits_hpp
#define DCSRegister8Bits_hpp
#include "DCSComponentArray.hpp"
class DCSRegister1Bit;
class DCSNode;

class DCSRegister8Bits: public DCSComponent {
private:
	DCSComponentArray<DCSRegister1Bit> registerArray;
	DCSComponentArray<DCSNode> nodeArray;
public:
	DCSRegister8Bits(std::string name);
	
	DCSComponent* getOutComponent(unsigned short &outPinNum) override;
	DCSComponent* getInComponent(unsigned short &inPinNum) override;
	void updateOut() override;
};

#endif /* DCSRegister8Bits_hpp */
