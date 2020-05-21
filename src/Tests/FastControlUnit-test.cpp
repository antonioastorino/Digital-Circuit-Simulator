#include "DCSAddressDecoder8Bits.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSInstructionSet.hpp"
#include "DCSLog.hpp"
#include "DCSOr.hpp"
#include "DCSDisplayNBits.hpp"

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

	//PLD 
    DCSAddressDecoder8Bits dec0("dec0");
    DCSComponentArray<DCSInput> inArr0("inArr", 8);
    DCSInput inGND("inGND");
    DCSDisplayNBits dispIn("in", 8);
    DCSDisplayNBits dispOut("out", 16);
    DCSComponentArray<DCSOr>* orArr0[16];
	DCSComponentArray<DCSOr>* orArr1[16];
	DCSComponentArray<DCSOr>* orArr2[16];
	DCSComponentArray<DCSOr>* orArr3[16];
	DCSComponentArray<DCSOr>* orArr4[16];
	DCSComponentArray<DCSOr>* orArr5[16];
	DCSComponentArray<DCSOr>* orArr6[16];
	DCSOr *or7[16];
    for (int i = 0; i < 16; i++) {
		// instantiation
        orArr0[i] = new DCSComponentArray<DCSOr>("orArr0", 128);
		orArr1[i] = new DCSComponentArray<DCSOr>("orArr1", 64);
		orArr2[i] = new DCSComponentArray<DCSOr>("orArr1", 32);
		orArr3[i] = new DCSComponentArray<DCSOr>("orArr1", 16);
		orArr4[i] = new DCSComponentArray<DCSOr>("orArr1", 8);
		orArr5[i] = new DCSComponentArray<DCSOr>("orArr1", 4);
		orArr6[i] = new DCSComponentArray<DCSOr>("orArr1", 2);
		or7[i] = new DCSOr("or7");
		// connection
		orArr0[i]->connect(orArr1[i]);
		orArr1[i]->connect(orArr2[i]);
		orArr2[i]->connect(orArr3[i]);
		orArr3[i]->connect(orArr4[i]);
		orArr4[i]->connect(orArr5[i]);
		orArr5[i]->connect(orArr6[i]);
		orArr6[i]->connect(or7[i]);
		or7[i]->connect(&dispOut, 0, i);
	}



    for (uint8_t i = 0; i < 8; i++) {
        inArr0[i]->makeSquareWave((hcp) << i);
    }

    size_t decPinNum = 0;
    for (size_t instr = 0; instr < 32; instr++) {
        for (size_t uCode = 0; uCode < 8; uCode++) {
            for (uint16_t bit = 0; bit < 16; bit++) {
                bool val = (data[instr][uCode] >> bit) & 1;
                if (val) {
                    dec0.connect(orArr0[bit], decPinNum, decPinNum);
                } else {
                    inGND.connect(orArr0[bit], 0, decPinNum);
                }
            }
            decPinNum++;
        }
    }

    inArr0.connect(&dec0);
    inArr0.connect(&dispIn);

    DCSEngine::run(256 * hcp, true);
}