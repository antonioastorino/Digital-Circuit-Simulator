#include "DCSMemoryProgrammer.hpp"
#include "DCSEngine.hpp"
#include "DCSLog.hpp"

DCSMemoryProgrammer::DCSMemoryProgrammer(DCSRam16x8 *memory):
memory(memory) {
	unsigned short hp = memory->getTimeDelay();
	DCSEngine::setHalfClockPeriod(hp);
	DCSEngine::initialize();
	
	unsigned short inputPin;
	// Clear active
	inputPin = 2;
	memory->getInComponent(inputPin)->setIn(1, inputPin);
	for (unsigned short i = 0; i < hp; i++) {
		DCSEngine::updateOutputs();
		DCSEngine::propagateValues();
	}
	DCSLog::output("CLEAR", "1 - Erasing memory\n");
	// Clear disabled
	inputPin = 2;
	memory->getInComponent(inputPin)->setIn(0, inputPin);
	for (unsigned short i = 0; i < hp; i++) {
		DCSEngine::updateOutputs();
		DCSEngine::propagateValues();
	}
	DCSLog::output("CLEAR", "0 - Memory erased\n");
}

void DCSMemoryProgrammer::program(unsigned short address, unsigned short value) {

	unsigned short hp = memory->getTimeDelay();
	unsigned short inputPin;
	
	std::stringstream message;
	message << " ADDR=";
	// set addresses
	for (unsigned short i = 0; i < 4; i++) {
		inputPin = i + 13;
		memory->getInComponent(inputPin)->setIn((address >> i) & 1, inputPin);
		message << ((address >> (3 - i)) & 1);
	}
	message << " DATA=";
	// set input value
	for (unsigned short i = 0; i < 8; i++) {
		inputPin = i + 5;
		memory->getInComponent(inputPin)->setIn((value >> i) & 1, inputPin);
		message << ((value >> (7 - i)) & 1);
	}
	message << '\n';
	DCSLog::output("Writing", message.str());
	
	// enable write
	inputPin = 4;
	memory->getInComponent(inputPin)->setIn(1, inputPin);

	// clock high
	inputPin = 1;
	memory->getInComponent(inputPin)->setIn(1, inputPin);
	for (unsigned short i = 0; i < hp; i++) {
		DCSEngine::updateOutputs();
		DCSEngine::propagateValues();
//		DCSEngine::printLogicLevels();
	}
	// clock low
	inputPin = 1;
	memory->getInComponent(inputPin)->setIn(0, inputPin);
//	// disable write
//	inputPin = 4;
//	memory->getInComponent(inputPin)->setIn(0, inputPin);
	for (unsigned short i = 0; i < hp; i++) {
		DCSEngine::updateOutputs();
		DCSEngine::propagateValues();
//		DCSEngine::printLogicLevels();
	}
}

void DCSMemoryProgrammer::program(unsigned short address,
								  unsigned short instruction,
								  unsigned short operand) {
	program(address, (instruction << 4) | operand);
}
