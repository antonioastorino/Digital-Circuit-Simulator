#ifndef DCSSRLatch_hpp
#define DCSSRLatch_hpp
#include "DCSNor.hpp"

/**
 * @class DCSSRLatch
 * SR latch.
 *
 * @pinout
 * In  0 - Reset
 * In  1 - Set
 * Out 0 - Q
 * Out 1 - !Q
 * @end_pinout
 */
class DCSSRLatch : public DCSComponent {
private:
    DCSNor nor0;
    DCSNor nor1;

public:
    DCSSRLatch(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSSRLatch_hpp */
