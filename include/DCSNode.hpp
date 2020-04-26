#ifndef DCSNode_hpp
#define DCSNode_hpp
#include "DCSComponent.hpp"

class DCSNode : public DCSComponent {
public:
    DCSNode(std::string name);

    void updateOut() override;

    void setIn(bool inVal, uint16_t inPinNum) override;
    void setIn(uint64_t inVec) override;

    uint64_t getAllReachedQWord() override;
};

#endif /* DCSNode_hpp */
