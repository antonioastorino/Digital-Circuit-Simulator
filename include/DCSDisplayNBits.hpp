#ifndef DCSDisplayNBits_hpp
#define DCSDisplayNBits_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSDisplayNBits
 *
 *
 */
class DCSDisplayNBits : public DCSComponent {
private:
    uint16_t numOfBits;
    uint16_t numOfDecimalDigits;

public:
    DCSDisplayNBits(std::string name, uint16_t numOfBits);
    void updateOut() override;
};

#endif /* DCSDisplayNBits_hpp */
