#ifndef DCSNot_hpp
#define DCSNot_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSNot
 * NOT gate
 */
class DCSNot: public DCSComponent {
public:
	DCSNot(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNot_hpp */
