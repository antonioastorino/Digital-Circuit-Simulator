#ifndef DCSNand_hpp
#define DCSNand_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSNand
 * Implements the NAND gate
 */
class DCSNand: public DCSComponent {
public:
	DCSNand(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNand_hpp */
