#ifndef DCSNot_hpp
#define DCSNot_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"

/**
 * @class DCSNot
 * NOT gate
 */
class DCSNot : public DCSComponent
{
public:
    DCSNot(std::string name);

    void updateOut() override;
};

#if TEST == 1
#include "DCSEngine.hpp"
void notLoopTest();
#endif

#endif /* DCSNot_hpp */
