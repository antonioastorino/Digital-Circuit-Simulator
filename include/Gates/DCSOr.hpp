#ifndef DCSOr_hpp
#define DCSOr_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"

/**
 * @class DCSOr
 * OR gate
 */
class DCSOr : public DCSComponent
{
public:
    DCSOr(std::string name);

    void updateOut() override;
};

#if TEST == 1
void orTest();
#endif

#endif /* DCSOr_hpp */
