#include "DCSPLD8In16Out.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSInstructionSet.hpp"
#include "DCSEngine.hpp"
#include "DCSLog.hpp"
#include "DCSRam256x16.hpp"

void fastControlUnitTest() {
    DCSLog::printTestName("Fast control unit");
	uint64_t hcp = 14;
    DCSEngine::initialize(hcp);
    
    DCSRam256x16 cuRam("cuRam");
    DCSEngine::programControlUnit(&cuRam, false);

    DCSEngine::useRamElements();

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
    DCSDisplayNBits dispROut("Rout", 16);
    DCSPLD8In16Out cu0("cu0", data);
    DCSInput inGND("inGND");
    DCSInput inVCC("inVCC");
    // DCSInput clk("clk");
    // connect RAM data in to GND
    for (int i = 0; i < 16; i++) {
        inGND.connect(&cuRam, 0, i);
    }
    // connect address line to RAM
    inArr0.connect(&cuRam, {0, 7}, {16, 23});

    // connect RAM ctrl signals
    for (int i = 24; i <= 27; i++) {
        inGND.connect(&cuRam, 0, i);
    }
    inVCC.connect(&cuRam, 0, 28); // Output enable

    inArr0.connect(&cu0);
    inArr0.connect(&dispIn);
    cu0.connect(&dispOut);
    cuRam.connect(&dispROut);
    // make signals
    for (uint8_t i = 0; i < 8; i++) {
        inArr0[i]->makeSquareWave((hcp) << i);
    }
    inVCC.makeSignal(1);


    DCSEngine::run(256 * hcp, true);
}