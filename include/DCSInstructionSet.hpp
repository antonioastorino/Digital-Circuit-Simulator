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
const uint16_t JZ  = 0b1000; // Jump if SUB returned zero
const uint16_t OUT = 0b1110; // Output
const uint16_t HLT = 0b1111; // Halt

const uint16_t HT = 0b1000000000000000; // bit 15
const uint16_t MI = 0b0100000000000000; // bit 14
const uint16_t RI = 0b0010000000000000; // bit 13
const uint16_t RO = 0b0001000000000000; // bit 12
const uint16_t IO = 0b0000100000000000; // bit 11
const uint16_t II = 0b0000010000000000; // bit 10
const uint16_t AI = 0b0000001000000000; // bit 9
const uint16_t AO = 0b0000000100000000; // bit 8
const uint16_t EO = 0b0000000010000000; // bit 7
const uint16_t SU = 0b0000000001000000; // bit 6
const uint16_t BI = 0b0000000000100000; // bit 5
const uint16_t OI = 0b0000000000010000; // bit 4
const uint16_t CE = 0b0000000000001000; // bit 3
const uint16_t CO = 0b0000000000000100; // bit 2
const uint16_t J  = 0b0000000000000010; // bit 1
const uint16_t FI = 0b0000000000000001; // bit 0

#endif /* DCSInstructionSet_hpp */