#ifndef DCSNode_hpp
#define DCSNode_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSNode
 *
 * This component provides a single access point to several connections with zero latency. It has
 * one input and one output. Using this component is essential when building composite components.
 * For example, assuming to have component `A` composed of 2 basic componets, `A0` and `A1`. Suppose
 * also that `A0` and `A1` should receive the same input `I`. There is no way for `A` to provide a
 * single connection to both `A0` and `A1` to the external logic. However, by defining a node `N0`,
 * `A` can connect `I` to the input of `N0` and connect the output of `N0` to both `A0` and `A1`.
 *
 * Nodes are also used to create busses and avoid to connect components to each other directly.
 * Instead, one can connect a node to all commponets' inputs and all (tri-state'd) components'
 * outputs to a node.
 */
class DCSNode : public DCSComponent {
public:
    DCSNode(std::string name);

    void updateOut() override;

    void setIn(bool inVal, uint16_t inPinNum) override;
};

#endif /* DCSNode_hpp */
