#ifndef DCSAnd6_hpp
#define DCSAnd6_hpp
#include "DCSAnd.hpp"
#include "DCSCommon.hpp"
#include "DCSComponentArray.hpp"
class DCSAnd3;

/**
 * @class DCSAnd6
 * AND gate with 6 inputs as an array of two DCSAnd3 AND'ed together by an AND gate
 */
class DCSAnd6 : public DCSComponent
{
private:
    DCSComponentArray<DCSAnd3> and3array;
    DCSAnd and0;

public:
    DCSAnd6(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};
#if TEST == 1
void and6Test();
#endif
#endif /* DCSAnd6_hpp */
