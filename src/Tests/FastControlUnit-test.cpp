#include "DCSPLD8In16Out.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSInstructionSet.hpp"
#include "DCSEngine.hpp"
#include "DCSLog.hpp"

void fastControlUnitTest() {
    DCSLog::printTestName("Fast control unit");
	uint64_t hcp = 10;
    DCSEngine::initialize(hcp);

    const uint16_t HLT = 0b1000000000000000; // bit 15
    const uint16_t MI  = 0b0100000000000000; // bit 14
    const uint16_t RI  = 0b0010000000000000; // bit 13
    const uint16_t RO  = 0b0001000000000000; // bit 12
    const uint16_t IO  = 0b0000100000000000; // bit 11
    const uint16_t II  = 0b0000010000000000; // bit 10
    const uint16_t AI  = 0b0000001000000000; // bit 9
    const uint16_t AO  = 0b0000000100000000; // bit 8
    const uint16_t EO  = 0b0000000010000000; // bit 7
    const uint16_t SU  = 0b0000000001000000; // bit 6
    const uint16_t BI  = 0b0000000000100000; // bit 5
    const uint16_t OI  = 0b0000000000010000; // bit 4
    const uint16_t CE  = 0b0000000000001000; // bit 3
    const uint16_t CO  = 0b0000000000000100; // bit 2
    const uint16_t J   = 0b0000000000000010; // bit 1
    // const uint16_t ??  = 0b0000000000000001;

    const uint16_t data[32][8] = {
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 0000 NOP
        {MI | CO, RO | II | CE, IO | MI, RO | AI, 0, 0, 0, 0},            // 0001 LDA
        {MI | CO, RO | II | CE, IO | MI, RO | BI, EO | AI, 0, 0, 0},      // 0010 ADD
        {MI | CO, RO | II | CE, IO | MI, RO | BI, EO | AI | SU, 0, 0, 0}, // 0011 SUB
        {MI | CO, RO | II | CE, IO | MI, AO | RI, 0, 0, 0, 0},            // 0100 STA
        {MI | CO, RO | II | CE, IO | AI, 0, 0, 0, 0, 0},                  // 0101 LDI
        {MI | CO, RO | II | CE, IO | J, 0, 0, 0, 0, 0},                   // 0110
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 0111
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1000
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1001
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1010
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1011
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1100
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1101
        {MI | CO, RO | II | CE, AO | OI, 0, 0, 0, 0, 0},                  // 1110 OUT
        {MI | CO, RO | II | CE, HLT, 0, 0, 0, 0, 0},                      // 1111 HLT
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 0000 NOP
        {MI | CO, RO | II | CE, IO | MI, RO | AI, 0, 0, 0, 0},            // 0001 LDA
        {MI | CO, RO | II | CE, IO | MI, RO | BI, EO | AI, 0, 0, 0},      // 0010 ADD
        {MI | CO, RO | II | CE, IO | MI, RO | BI, EO | AI | SU, 0, 0, 0}, // 0011 SUB
        {MI | CO, RO | II | CE, IO | MI, AO | RI, 0, 0, 0, 0},            // 0100 STA
        {MI | CO, RO | II | CE, IO | AI, 0, 0, 0, 0, 0},                  // 0101 LDI
        {MI | CO, RO | II | CE, IO | J, 0, 0, 0, 0, 0},                   // 0110
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 0111
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1000
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1001
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1010
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1011
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1100
        {MI | CO, RO | II | CE, 0, 0, 0, 0, 0, 0},                        // 1101
        {MI | CO, RO | II | CE, AO | OI, 0, 0, 0, 0, 0},                  // 1110 OUT
        {MI | CO, RO | II | CE, HLT, 0, 0, 0, 0, 0}                       // 1111 HLT
    };

	
    DCSComponentArray<DCSInput> inArr0("inArr", 8);
    DCSDisplayNBits dispIn("in", 8);
    DCSDisplayNBits dispOut("out", 16);
    DCSPLD8In16Out cu0("cu0", data);


    for (uint8_t i = 0; i < 8; i++) {
        inArr0[i]->makeSquareWave((hcp) << i);
    }

    inArr0.connect(&cu0);
    inArr0.connect(&dispIn);
    cu0.connect(&dispOut);

    DCSEngine::run(256 * hcp, true);
}