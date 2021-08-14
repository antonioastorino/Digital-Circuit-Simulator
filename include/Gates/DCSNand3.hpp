#ifndef DCSNand3_hpp
#define DCSNand3_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"
/**
 * @class DCSNand3
 * NAND gate with 3 inputs
 */
class DCSNand3 : public DCSComponent
{
public:
    DCSNand3(std::string name);

    void updateOut() override;
};
#if TEST == 1
void nand3Test();
#endif

#endif /* DCSNand3_hpp */
