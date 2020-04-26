#ifndef DCSNand3_hpp
#define DCSNand3_hpp
#include "DCSComponent.hpp"
/**
 * @class DCSNand3
 * Implements the NAND gate with 3 inputs
 */
class DCSNand3: public DCSComponent {
public:
	DCSNand3(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNand3_hpp */
