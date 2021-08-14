#ifndef DCSOr_hpp
#define DCSOr_hpp
#include "DCSComponent.hpp"
#include "DCSCommon.hpp"

/**
 * @class DCSOr
 * OR gate
 */
class DCSOr: public DCSComponent {
public:
	DCSOr(std::string name);
	
	void updateOut() override;
};

#if TEST == 1
void orTest();
#endif

#endif /* DCSOr_hpp */
