#ifndef DCSTriStateBuffer_hpp
#define DCSTriStateBuffer_hpp
#include "DCSComponent.hpp"
#include "DCSCommon.hpp"
/*
 When input 1 is low, the output does not change and does not propagate (the wire ignores it).
 When input 1 is high, the output matches the value of input 0 but delayed by tau.
 */

class DCSTriStateBuffer: public DCSComponent {

public:
	DCSTriStateBuffer(std::string name);
	
	void updateOut() override;
	
	void enable() override;
	void disable() override;
};

#if TEST == 1
void triStateBufferTest();
#endif

#endif /* DCSTriStateBuffer_hpp */
