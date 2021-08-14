#ifndef DCSDisplayNBits_hpp
#define DCSDisplayNBits_hpp
#include "DCSComponent.hpp"
#include "DCSCommon.hpp"

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

#if TEST == 1
void displayTest();
#endif

#endif /* DCSDisplayNBits_hpp */
