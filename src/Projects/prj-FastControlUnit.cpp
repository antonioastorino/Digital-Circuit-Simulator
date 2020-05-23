#include "prj-FastControlUnit.hpp"

void fastControlUnitTest() {
    DCSLog::printTestName("Fast control unit");
    uint64_t hcp = 14;
    DCSEngine::initialize(hcp);

    // clang-format off
    const uint16_t data[32][8] = {
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 0000 NOP
        { MI|CO, RO|II|CE, IO|MI, RO|AI, 0,              0, 0, 0 }, // 0001 LDA
        { MI|CO, RO|II|CE, IO|MI, RO|BI, EO|AI,          0, 0, 0 }, // 0010 ADD
        { MI|CO, RO|II|CE, IO|MI, RO|BI|SU, EO|AI|SU|FI, 0, 0, 0 }, // 0011 SUB
        { MI|CO, RO|II|CE, IO|MI, AO|RI, 0,              0, 0, 0 }, // 0100 STA
        { MI|CO, RO|II|CE, IO|AI, 0,     0,              0, 0, 0 }, // 0101 LDI
        { MI|CO, RO|II|CE, IO|J,  0,     0,              0, 0, 0 }, // 0110 JMP
        { MI|CO, RO|II|CE, IO|MI, RO|BI, 0,              0, 0, 0 }, // 0111 LDB
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1000 JZ
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1001
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1010
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1011
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1100
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1101
        { MI|CO, RO|II|CE, AO|OI, 0,     0,              0, 0, 0 }, // 1110 OUT
        { MI|CO, RO|II|CE, HT,    0,     0,              0, 0, 0 }, // 1111 HLT
        // only if A == B
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 0000 NOP
        { MI|CO, RO|II|CE, IO|MI, RO|AI, 0,              0, 0, 0 }, // 0001 LDA
        { MI|CO, RO|II|CE, IO|MI, RO|BI, EO|AI,          0, 0, 0 }, // 0010 ADD
        { MI|CO, RO|II|CE, IO|MI, RO|BI|SU, EO|AI|SU|FI, 0, 0, 0 }, // 0011 SUB
        { MI|CO, RO|II|CE, IO|MI, AO|RI, 0,              0, 0, 0 }, // 0100 STA
        { MI|CO, RO|II|CE, IO|AI, 0,     0,              0, 0, 0 }, // 0101 LDI
        { MI|CO, RO|II|CE, IO|J,  0,     0,              0, 0, 0 }, // 0110 JMP
        { MI|CO, RO|II|CE, IO|MI, RO|BI, 0,              0, 0, 0 }, // 0111 LDB
        { MI|CO, RO|II|CE, IO|J,  0,     0,              0, 0, 0 }, // 1000 JZ
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1001
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1010
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1011
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1100
        { MI|CO, RO|II|CE, 0,     0,     0,              0, 0, 0 }, // 1101
        { MI|CO, RO|II|CE, AO|OI, 0,     0,              0, 0, 0 }, // 1110 OUT
        { MI|CO, RO|II|CE, HT,    0,     0,              0, 0, 0 }  // 1111 HLT
    };
    // clang-format on

    DCSComponentArray<DCSInput> inArr0("inArr", 8);
    DCSDisplayNBits dispIn("in", 8);
    DCSDisplayNBits dispOut("out", 16);
    DCSPLD8In16Out cu0("cu0", data);

    inArr0.connect(&cu0);
    inArr0.connect(&dispIn);
    cu0.connect(&dispOut);
    // make signals
    for (uint8_t i = 0; i < 8; i++) {
        inArr0[i]->makeSquareWave((hcp) << i);
    }

    DCSEngine::run(256 * hcp, true);
}