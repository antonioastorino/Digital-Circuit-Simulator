#ifndef DCSXor_hpp
#define DCSXor_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"

class DCSXor : public DCSComponent
{
public:
    DCSXor(std::string name);

    void updateOut() override;
};

#if TEST == 1
void xorTest();
#endif
#endif /* DCSXor_hpp */
