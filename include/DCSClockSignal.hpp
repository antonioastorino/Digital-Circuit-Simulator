#ifndef DCSClockSignal_hpp
#define DCSClockSignal_hpp
#include "DCSArbitrarySignal.hpp"

/**
 * @class DCSClockSignal
 * Generates a square wave with period 2 * `halfPeriod`
 */
class DCSClockSignal: public DCSArbitrarySignal {
private:
	uint16_t halfPeriod;
public:
	DCSClockSignal(uint16_t halfPeriod=0, bool initVal=0);
	
	bool getVal(uint32_t step) override;
};

#endif /* DCSClockSignal_hpp */
