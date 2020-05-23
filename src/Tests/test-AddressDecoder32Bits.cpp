#include "test-AddressDecoder32Bits.hpp"

void addressDecoder32BitsTest() {
	DCSLog::printTestName("32-bit address decoder");
	uint16_t hp = 1;
	DCSEngine::initialize(hp);

	DCSComponentArray<DCSInput> inArray("In", 8);
	DCSAddressDecoder8Bits dec8("dec8");
	DCSDisplayNBits dispIn("in", 8);
	DCSDisplayNBits dispOutA("outA", 32);
	DCSDisplayNBits dispOutB("outB", 32);
	DCSDisplayNBits dispOutC("outC", 32);
	DCSDisplayNBits dispOutD("outD", 32);
	DCSDisplayNBits dispOutE("outE", 32);
	DCSDisplayNBits dispOutF("outF", 32);
	DCSDisplayNBits dispOutG("outG", 32);
	DCSDisplayNBits dispOutH("outH", 32);
	
	inArray.connect(&dec8);
	inArray.connect(&dispIn);
	uint16_t startPin = 0;
	dec8.connect(&dispOutA, {0, 31}, {0, 31});
	dec8.connect(&dispOutB, {32, 63}, {0, 31});
	dec8.connect(&dispOutC, {64, 95}, {0, 31});
	dec8.connect(&dispOutD, {96, 127}, {0, 31});
	dec8.connect(&dispOutE, {128, 159}, {0, 31});
	dec8.connect(&dispOutF, {160, 191}, {0, 31});
	dec8.connect(&dispOutG, {192, 223}, {0, 31});
	dec8.connect(&dispOutH, {224, 255}, {0, 31});
	
	for (uint16_t i = 0; i < 8; i ++) {
		inArray[i]->makeSquareWave(hp<<i, 0);
	}

	DCSEngine::run(256*hp+3, false);
}

