//
//  DCSHeader.h
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSHeader_h
#define DCSHeader_h

#define LOG_LEVEL 1

#include <sstream>
#include <iostream>
#include <vector>

#ifndef ushort
#define ushort unsigned short
#endif
typedef std::vector<uint64_t> binary_signal;
void printTestName(std::string testName);
void ramTest();
void ramProgrammerTest();

// TODO: put somewhere else
struct DCSPinNumRange {
	ushort startPinNum;
	ushort endPinNum;
	DCSPinNumRange(ushort startPinNum, ushort endPinNum) :
	startPinNum(startPinNum),
	endPinNum(endPinNum) {}
};

#include "DCSLog.hpp"

#include "DCSArbitrarySignal.hpp"
#include "DCSClockSignal.hpp"

#include "DCSComponent.hpp"
#include "DCSComponentArray.hpp"

#include "DCSAnd.hpp"
#include "DCSAnd3.hpp"
#include "DCSAnd4.hpp"
#include "DCSAnd6.hpp"
#include "DCSNand.hpp"
#include "DCSOr.hpp"
#include "DCSXor.hpp"
#include "DCSNot.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNor.hpp"
#include "DCSNor3.hpp"
#include "DCSNand3.hpp"

#include "DCSInput.hpp"
#include "DCSOutput.hpp"

#include "DCSWire.hpp"
#include "DCSNode.hpp"

#include "DCSAddressDecoder4Bits.hpp"

#include "DCSMux2to1.hpp"

#include "DCSTriStateBuffer.hpp"
#include "DCSTriStateBuffer8Bits.hpp"

#include "DCSSRLatch.hpp"
#include "DCSDLatch.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSRam16x8.hpp"


#include "DCSClockDiv2WithEnableAndLoad.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

#include "DCSFullAdder.hpp"
#include "DCSRippleAdder8Bits.hpp"

#include "DCSDisplayNBits.hpp"

#include "DCSMemoryProgrammer.hpp"

#include "DCSEngine.hpp"

#endif /* DCSHeader_h */
