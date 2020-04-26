
#include "DCSInput.hpp"
#include "DCSClockSignal.hpp"
#include "DCSEngine.hpp"

DCSInput::DCSInput(std::string name) :
DCSComponent(name, false),
constValue(0) {
	signal = new DCSArbitrarySignal(binary_signal{0});
	initialize();
}

DCSInput::DCSInput(std::string name, bool constValue) :
DCSComponent(name, false),
constValue(constValue){
	signal = new DCSArbitrarySignal(binary_signal{0});
	initialize();
}

DCSInput::DCSInput(std::string name, binary_signal signal, bool synch) :
DCSComponent(name, false),
constValue(0) {
	this->signal = new DCSArbitrarySignal(signal, synch);
	hasSignal = true;
	initialize();
}

void DCSInput::initialize() {
	timeDelay = 0;
	numOfInPins = 0;
	numOfOutPins = 1;
	DCSEngine::addInput(this);
}

DCSInput::~DCSInput() {
	delete signal;
}

void DCSInput::makeSignal(bool constValue) {
	this->constValue = constValue;
};

void DCSInput::makeSignal(binary_signal signal, bool initVal, bool synch) {
	this->signal = new DCSArbitrarySignal(signal, initVal, synch);
	hasSignal = true;
}

void DCSInput::makeSignal(std::string signal, bool synch) {
	this->signal = new DCSArbitrarySignal(signal, synch);
	hasSignal = true;
}

void DCSInput::makeClock(unsigned short halfPeriod, bool initVal) {
	this->signal = new DCSClockSignal(halfPeriod, initVal);
	hasSignal = true;
}

void DCSInput::updateOut() {
	if (hasSignal) out = signal->getVal(DCSEngine::getStepNumber());
	else out = constValue;
}
