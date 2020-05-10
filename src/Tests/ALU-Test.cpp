#include "DCSALU.hpp"
#include "DCSLog.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSDisplayNBits.hpp"

void aluTest() {
	DCSLog::printTestName("ALU"); {
		uint16_t masterClockHP = 20;
		DCSEngine::initialize(masterClockHP);

		DCSDisplayNBits dispA("dispA", 8);
		DCSDisplayNBits dispB("dispB", 8);
		DCSDisplayNBits dispE("dispE", 8);
		
		DCSALU alu("alu");
		DCSComponentArray<DCSInput> inA("A", 8);
		DCSComponentArray<DCSInput> inB("B", 8);
		DCSInput su("SU");
		DCSComponentArray<DCSOutput> sum("E", 8);

		inA.connect(&alu, {0, 7}, {0, 7});
		inA.connect(&dispA, {0, 7}, {0, 7});
		
		inB.connect(&alu, {0, 7}, {8, 15});
		inB.connect(&dispB, {0, 7}, {0, 7});
		
		su.connect(&alu, 0, 16, "SU");
		alu.connect(&sum);
		alu.connect(&dispE);

		inA[3]->makeSignal(1);
		inA[4]->makeSignal(1);
		inA[5]->makeSignal(1);
		inA[6]->makeSignal(1);
		inB[0]->makeSignal(1);
		inB[5]->makeSignal(1);

		su.makeSignal(1);

		DCSEngine::run(1 * masterClockHP, false);
	}
}