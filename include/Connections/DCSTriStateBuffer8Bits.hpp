
#ifndef DCSTriStateBuffer8Bits_hpp
#define DCSTriStateBuffer8Bits_hpp
#include "DCSComponentArray.hpp"
#include "DCSNode.hpp"
#include "DCSTriStateBuffer.hpp"

/**
 * @class DCSTristateBuffer8Bits
 * Consists of an array of tri-state buffers sharing `Enable`
 *
 * @pinout
 * In 0   - Data in 0
 * In 1   - Data in 1
 * In 2   - Data in 2
 * In 3   - Data in 3
 * In 4   - Data in 4
 * In 5   - Data in 5
 * In 6   - Data in 6
 * In 7   - Data in 7
 * In 8   - Enable
 *
 * Out 0  - Data out 0
 * Out 1  - Data out 1
 * Out 2  - Data out 2
 * Out 3  - Data out 3
 * Out 4  - Data out 4
 * Out 5  - Data out 5
 * Out 6  - Data out 6
 * Out 7  - Data out 7
 * @end_pinout
 */
class DCSTriStateBuffer8Bits : public DCSComponent
{
private:
    DCSComponentArray<DCSTriStateBuffer> bufferArray;
    DCSNode node0;

public:
    DCSTriStateBuffer8Bits(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;

    void enable() override;
    void disable() override;
};

#endif /* DCSTriStateBuffer8Bits_hpp */
