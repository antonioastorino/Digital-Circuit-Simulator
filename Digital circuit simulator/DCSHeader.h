//
//  DCSHeader.h
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSHeader_h
#define DCSHeader_h


#include <sstream>
#include <iostream>
#include <vector>

typedef std::vector<uint64_t> binary_signal;

#include "DCSLog.hpp"

#include "DCSArbitrarySignal.hpp"
#include "DCSClockSignal.hpp"

#include "DCSComponent.hpp"
#include "DCSComponentArray.hpp"

#include "DCSAnd.hpp"
#include "DCSAnd3.hpp"
#include "DCSNand.hpp"
#include "DCSOr.hpp"
#include "DCSNot.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNor.hpp"
#include "DCSNor3.hpp"
#include "DCSNand3.hpp"
#include "DCSTriStateBuffer.hpp"

#include "DCSInput.hpp"
#include "DCSOutput.hpp"

#include "DCSWire.hpp"
#include "DCSNode.hpp"

#include "DCSSRLatch.hpp"
#include "DCSDLatch.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSRegister1Bit.hpp"

#include "DCSClockDiv2WithEnableAndLoad.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"


#include "DCSEngine.hpp"


#endif /* DCSHeader_h */
