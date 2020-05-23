#include "test-ALU.hpp"

void aluTest() {
	DCSLog::printTestName("ALU"); {
		uint16_t masterClockHP = 1;
		DCSEngine::initialize(masterClockHP);

		DCSDisplayNBits dispA("dispA", 8);
		DCSDisplayNBits dispB("dispB", 8);
		DCSDisplayNBits dispE("dispE", 8);
		
		DCSALU alu("alu");
		DCSComponentArray<DCSInput> inA("A", 8);
		DCSComponentArray<DCSInput> inB("B", 8);
		DCSInput su("SU");
		DCSOutput outZero("OZ");

		inA.connect(&alu, {0, 7}, {0, 7});
		inA.connect(&dispA, {0, 7}, {0, 7});
		
		inB.connect(&alu, {0, 7}, {8, 15});
		inB.connect(&dispB, {0, 7}, {0, 7});
		
		su.connect(&alu, 0, 16, "SU");
		alu.connect(&dispE,  {0, 7}, {0, 7});
		alu.connect(&outZero, 9, 0, "OZ");

		inA[0]->makeSignal(1);
		// inA[4]->makeSignal(1);
		inA[5]->makeSignal(1);
		// inA[6]->makeSignal(1);
		inB[0]->makeSignal(1);
		inB[5]->makeSignal(1);

		su.makeSignal(1);

		DCSEngine::run(30 * masterClockHP, false);
	}
}