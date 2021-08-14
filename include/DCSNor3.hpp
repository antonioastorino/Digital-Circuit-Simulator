#ifndef DCSNor3_hpp
#define DCSNor3_hpp
#include "DCSComponent.hpp"
#include "DCSCommon.hpp"

/**
 * @class DCSNor3
 * NOR gate with 3 inputs
 */
class DCSNor3: public DCSComponent {
public:
	DCSNor3(std::string name);
	
	void updateOut() override;
};
#if TEST == 1
void nor3Test();
#endif

#endif /* DCSNor3_hpp */
