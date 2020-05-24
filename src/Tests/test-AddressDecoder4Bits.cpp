#include "test-AddressDecoder4Bits.hpp"

void addressDecoderTest4Bits() {
	DCSLog::printTestName("4-bit address decoder");
	uint16_t hcp = 3;
	DCSEngine::initialize(hcp);
	DCSComponentArray<DCSInput> inArray0("IN", 4);
	// DCSComponentArray<DCSOutput> outArray0("OUT", 16);
	DCSDisplayNBits inDisp0("in", 4);
	DCSDisplayNBits outDisp0("out", 16);

	DCSAddressDecoder4Bits dec0("dec0");

	inArray0.connect(&dec0);
	inArray0.connect(&inDisp0);
	// dec0.connect(&outArray0);
	dec0.connect(&outDisp0);

	inArray0[0]->makeSquareWave(hcp);
	inArray0[1]->makeSquareWave(2 * hcp);
	inArray0[2]->makeSquareWave(4 * hcp);
	inArray0[3]->makeSquareWave(8 * hcp);

	DCSEngine::run(50, false);
}