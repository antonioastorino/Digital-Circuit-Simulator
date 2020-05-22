#ifndef DCSALU_hpp
#define DCSALU_hpp

#include "DCSRippleAdder8Bits.hpp"
#include "DCSComponent.hpp" 
#include "DCSXor.hpp"
#include "DCSXor.hpp"
#include "DCSNor3.hpp"
#include "DCSAnd3.hpp"
#include "DCSNot.hpp"
#include "DCSComponentArray.hpp"
#include "DCSNode.hpp"

/**
 * @class DCSALU
 * 
 * ALU capable of adding (A+B) or subtracting (A-B) 8-bit numbers.
 * 
 * @pinout
 * In 0   - A 0
 * In 1   - A 1
 * In 2   - A 2
 * In 3   - A 3
 * In 4   - A 4
 * In 5   - A 5
 * In 6   - A 6
 * In 7   - A 7
 * In 8   - B 0
 * In 9   - B 1
 * In 10  - B 2
 * In 11  - B 3
 * In 12  - B 4
 * In 13  - B 5
 * In 14  - B 6
 * In 15  - B 7
 * In 16  - SU (subtract)
 * 
 * Out 0  - E 0
 * Out 1  - E 1
 * Out 2  - E 2
 * Out 3  - E 3
 * Out 4  - E 4
 * Out 5  - E 5
 * Out 6  - E 6
 * Out 7  - E 7
 * Out 8  - Overflow
 * Out 9  - Zero
 * @end_pinout
 */

class DCSALU: public DCSComponent {
private:
	DCSRippleAdder8Bits adder0;
	DCSComponentArray<DCSXor> xorArr0;
	DCSComponentArray<DCSNor3> nor3Array0;
	DCSAnd3 and3_0;
	DCSNot not0;
	DCSNode nodeSU;

public:
	DCSALU(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
	DCSComponent* getOutComponent(uint16_t outPinNum) override;

	void updateOut() override; 
};

#endif /* DCSALU_hpp */