#ifndef DCSMemoryProgrammer_hpp
#define DCSMemoryProgrammer_hpp
#include "DCSRam16x8.hpp"

class DCSMemoryProgrammer {
private:
	DCSRam16x8 *memory;
public:
	DCSMemoryProgrammer() = delete;
	DCSMemoryProgrammer(DCSRam16x8 *memory);
	
	void program(unsigned short address, unsigned short value);
	void program(unsigned short address, unsigned short instruction, unsigned short operand);
};

#endif /* DCSMemoryProgrammer_hpp */
