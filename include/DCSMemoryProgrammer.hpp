#ifndef DCSMemoryProgrammer_hpp
#define DCSMemoryProgrammer_hpp
#include "DCSRam16x8.hpp"

class DCSMemoryProgrammer {
private:
	DCSRam16x8 *memory;
public:
	DCSMemoryProgrammer() = delete;
	DCSMemoryProgrammer(DCSRam16x8 *memory);
	
	void program(uint16_t address, uint16_t value);
	void program(uint16_t address, uint16_t instruction, uint16_t operand);
};

#endif /* DCSMemoryProgrammer_hpp */
