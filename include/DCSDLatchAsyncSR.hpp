
#ifndef DCSDLatchAsyncSR_hpp
#define DCSDLatchAsyncSR_hpp
#include "DCSNode.hpp"
#include "DCSNor3.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNot.hpp"
#include "DCSAnd.hpp"

/**
 * @class DCSDLatchAsyncSR
 * Implements a D Latch with asynchronous Set and Reset
 * Pinout:
 * 0 -> In Data
 * 1 -> In Enable
 * 2 -> In Asynchronous Reset (Clear)
 * 3 -> In Asynchronous Set (Preset)
 * 
 * The time diagram is a merge of D-Latch and SR-Latch: when S and R are both low, this component behaves exactly like a D-Latch. When Enable is low, it behaves exactly like an SR-Latch.
 * NOTE: do now use Enable when S or R are high.
 */
class DCSDLatchAsyncSR: public DCSComponent {
private:
	DCSNor3 nor3_0      = DCSNor3(name + "-Nor0");
	DCSNor3 nor3_1      = DCSNor3(name + "-Nor1");
	DCSAnd and0         = DCSAnd(name + "-And0");
	DCSAnd and1         = DCSAnd(name + "-And1");
	DCSNot not0         = DCSNot(name + "-Not0");
	DCSUnitDelay del0   = DCSUnitDelay(name + "-Del0");
	DCSNode node0       = DCSNode(name + "-Node0");
	DCSNode node1       = DCSNode(name + "-Node1");
public:
	DCSDLatchAsyncSR(std::string name);

	DCSComponent* getInComponent(uint16_t &inPinNum) override;
	DCSComponent* getOutComponent(uint16_t &outPinNum) override;
	
	void updateOut() override;
};

#endif /* DCSDLatchAsyncSR_hpp */
