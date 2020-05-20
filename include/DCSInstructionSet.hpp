#ifndef DCSInstructionSet_hpp
#define DCSInstructionSet_hpp
#include <cstdint>

// Instruction set
const uint16_t NOP = 0b0000; // No operation
const uint16_t LDA = 0b0001; // Load A from RAM
const uint16_t ADD = 0b0010; // Add value from location in RAM to reg A and store in B
const uint16_t SUB = 0b0011; // Subtract value from location in RAM to reg A and store in B
const uint16_t STA = 0b0100; // Store A in RAM
const uint16_t LDI = 0b0101; // Load immediate to A reg
const uint16_t JMP = 0b0110; // Jump
const uint16_t LDB = 0b0111; // Load B from RAM
const uint16_t JEQ = 0b1000; // Jump if A == B
const uint16_t OUT = 0b1110; // Output
const uint16_t HLT = 0b1111; // Halt

#endif /* DCSInstructionSet_hpp */