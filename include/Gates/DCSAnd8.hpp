#ifndef DCSAnd8_hpp
#define DCSAnd8_hpp
#include "DCSAnd.hpp"
#include "DCSComponentArray.hpp"
class DCSAnd4;

/**
 * @class DCSAnd8
 * AND gate with 8 inputs as an array of two DCSAnd4 AND'ed together by an AND gate
 */
class DCSAnd8 : public DCSComponent
{
private:
    DCSComponentArray<DCSAnd4> m_and4Array;
    DCSAnd m_and0;

public:
    DCSAnd8(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSAnd8_hpp */
