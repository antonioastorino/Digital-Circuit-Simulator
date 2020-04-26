/*
 SR latch whose input pin 0 resets and 1 sets
 
 PINOUT:
 IN  0 - Reset
 IN  1 - Set
 OUT 0 - Q
 OUT 1 - !Q
*/
#ifndef DCSSRLatch_hpp
#define DCSSRLatch_hpp
#include "DCSNor.hpp"

class DCSSRLatch: public DCSComponent {
private:
	DCSNor nor0;
	DCSNor nor1;
public:
	DCSSRLatch(std::string name);

	DCSComponent* getInComponent(uint16_t &inPinNum) override;
	DCSComponent* getOutComponent(uint16_t &outPinNum) override;
	
	void updateOut() override;
};


#endif /* DCSSRLatch_hpp */
