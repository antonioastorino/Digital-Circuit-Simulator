#ifndef DCSAnd3_hpp
#define DCSAnd3_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSAnd3
 * AND gate with 3 inputs
 */
class DCSAnd3: public DCSComponent {
public:
	DCSAnd3(std::string name);
	
	void updateOut() override;
};

#endif /* DCSAnd3_hpp */
