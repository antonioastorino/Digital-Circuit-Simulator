# Makefile auto generated using custom generator
OBJCFLAGS=
CPPFLAGS=-Wall -Wextra -g -std=c++1z
CFLAGS=
MAINFLAGS=-Wall -Wextra -g -std=c++1z
BD=/Users/antonio/Projects/DCS/bin/..
OPT ?= 0
LIB=-lc++ -pthread
INC= -Iinclude \
 -Iinclude/Arithmetic \
 -Iinclude/Base \
 -Iinclude/Connections \
 -Iinclude/ControlUnits \
 -Iinclude/Core \
 -Iinclude/Counters \
 -Iinclude/Decoders \
 -Iinclude/Displays \
 -Iinclude/Gates \
 -Iinclude/Latches \
 -Iinclude/Latches-async-SR \
 -Iinclude/Memory \
 -Iinclude/Muxes-Demuxes \
 -Iinclude/Projects \
 -Iinclude/Signals \

.PHONY: all setup

all: setup

setup:
	@/bin/rm -rf dcs.app
	@mkdir -p \
	 \
	test/artifacts \
	build
	@if [ "$(MODE)" = "TEST" ]; then \
	[ `grep -c '^#define TEST 0' "$(BD)"/include/DCSCommon.hpp` -eq 1 ] && \
	sed -i.bak 's/^#define TEST 0/#define TEST 1/g' "$(BD)"/include/DCSCommon.hpp; \
	[ `grep -c '^#define MEM_ANALYSIS 0' "$(BD)"/include/DCSCommon.hpp` -eq 1 ] && \
	sed -i.bak 's/^#define MEM_ANALYSIS 0/#define MEM_ANALYSIS 1/g' "$(BD)"/include/DCSCommon.hpp; \
	make -C "$(BD)" OPT=$(OPT) build/dcs-test-o$(OPT); \
	else \
	[ `grep -c '^#define TEST 1' "$(BD)"/include/DCSCommon.hpp` -eq 1 ] && \
	sed -i.bak 's/^#define TEST 1/#define TEST 0/g' "$(BD)"/include/DCSCommon.hpp; \
	[ `grep -c '^#define MEM_ANALYSIS 1' "$(BD)"/include/DCSCommon.hpp` -eq 1 ] && \
	sed -i.bak 's/^#define MEM_ANALYSIS 1/#define MEM_ANALYSIS 0/g' "$(BD)"/include/DCSCommon.hpp; \
	make -C "$(BD)" OPT=$(OPT) build/dcs-o$(OPT); \
	fi

build/dcs-o$(OPT):\
	build/DCSNand3.o \
	build/DCSAnd8.o \
	build/DCSNor.o \
	build/DCSNot.o \
	build/DCSUnitDelay.o \
	build/DCSNand.o \
	build/DCSAnd6.o \
	build/DCSAnd.o \
	build/DCSOr.o \
	build/DCSAnd4.o \
	build/DCSNor3.o \
	build/DCSAnd3.o \
	build/DCSXor.o \
	build/DCSMux2To1.o \
	build/DCSEngine.o \
	build/DCSLog.o \
	build/DCSTimer.o \
	build/DCSRegister8BitsWithEnable.o \
	build/DCSRegister4Bits.o \
	build/DCSRam256x16.o \
	build/DCSRegister1Bit.o \
	build/DCSRam16x8.o \
	build/DCSRegister1BitWithEnable.o \
	build/DCSRegister16BitsWithEnable.o \
	build/DCSRegister8Bits.o \
	build/DCSSRLatch.o \
	build/DCSDFlipFlop.o \
	build/DCSDLatch.o \
	build/prj-countByThrees.o \
	build/prj-fastZeroFlagProgram.o \
	build/prj-FastControlUnit.o \
	build/prj-NoCUComputer.o \
	build/DCSClockSignal.o \
	build/DCSArbitrarySignal.o \
	build/DCSDisplayNBits.o \
	build/DCSNode.o \
	build/DCSWire.o \
	build/DCSTriStateBuffer.o \
	build/DCSOutput.o \
	build/DCSInput.o \
	build/DCSTriStateBuffer8Bits.o \
	build/DCSControlUnit4Bits.o \
	build/DCSControlUnit5Bits.o \
	build/DCSPLD8In16Out.o \
	build/DCSAddressDecoder8Bits.o \
	build/DCSAddressDecoder4Bits.o \
	build/DCSALU.o \
	build/DCSRippleAdder8Bits.o \
	build/DCSFullAdder.o \
	build/DCSClockDivider.o \
	build/DCSUpCounterWithLoadAndAsyncSR.o \
	build/main.o \
	build/DCSComponent.o \
	build/DCSComponentArray.o \
	build/DCSDFlipFlopAsyncSR.o \
	build/DCSDLatchAsyncSR.o \
	build/DCSJKLatchMasterSlaveAsyncSR.o 
	clang $(LIB) $(MAINFLAGS) -O$(OPT) $(INC) $(FRAMEWORKS) $^ -o $@

build/dcs-test-o$(OPT):\
	build/DCSNand3.o \
	build/DCSAnd8.o \
	build/DCSNor.o \
	build/DCSNot.o \
	build/DCSUnitDelay.o \
	build/DCSNand.o \
	build/DCSAnd6.o \
	build/DCSAnd.o \
	build/DCSOr.o \
	build/DCSAnd4.o \
	build/DCSNor3.o \
	build/DCSAnd3.o \
	build/DCSXor.o \
	build/DCSMux2To1.o \
	build/DCSEngine.o \
	build/DCSLog.o \
	build/DCSTimer.o \
	build/DCSRegister8BitsWithEnable.o \
	build/DCSRegister4Bits.o \
	build/DCSRam256x16.o \
	build/DCSRegister1Bit.o \
	build/DCSRam16x8.o \
	build/DCSRegister1BitWithEnable.o \
	build/DCSRegister16BitsWithEnable.o \
	build/DCSRegister8Bits.o \
	build/DCSSRLatch.o \
	build/DCSDFlipFlop.o \
	build/DCSDLatch.o \
	build/prj-countByThrees.o \
	build/prj-fastZeroFlagProgram.o \
	build/prj-FastControlUnit.o \
	build/prj-NoCUComputer.o \
	build/DCSClockSignal.o \
	build/DCSArbitrarySignal.o \
	build/DCSDisplayNBits.o \
	build/DCSNode.o \
	build/DCSWire.o \
	build/DCSTriStateBuffer.o \
	build/DCSOutput.o \
	build/DCSInput.o \
	build/DCSTriStateBuffer8Bits.o \
	build/DCSControlUnit4Bits.o \
	build/DCSControlUnit5Bits.o \
	build/DCSPLD8In16Out.o \
	build/DCSAddressDecoder8Bits.o \
	build/DCSAddressDecoder4Bits.o \
	build/DCSALU.o \
	build/DCSRippleAdder8Bits.o \
	build/DCSFullAdder.o \
	build/DCSClockDivider.o \
	build/DCSUpCounterWithLoadAndAsyncSR.o \
	build/main-test.o \
	build/DCSComponent.o \
	build/DCSComponentArray.o \
	build/DCSDFlipFlopAsyncSR.o \
	build/DCSDLatchAsyncSR.o \
	build/DCSJKLatchMasterSlaveAsyncSR.o 
	clang $(LIB) $(MAINFLAGS) -O$(OPT) $(INC) $(FRAMEWORKS) $^ -o $@

build/DCSNand3.o: src/Gates/DCSNand3.cpp \
	include/Gates/DCSNand3.hpp \
	include/DCSCommon.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAnd8.o: src/Gates/DCSAnd8.cpp \
	include/Gates/DCSAnd8.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSNor.o: src/Gates/DCSNor.cpp \
	include/Gates/DCSNor.hpp \
	include/DCSCommon.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSNot.o: src/Gates/DCSNot.cpp \
	include/Gates/DCSNot.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSEngine.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSUnitDelay.o: src/Gates/DCSUnitDelay.cpp \
	include/Gates/DCSUnitDelay.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSEngine.hpp \
	include/Core/DCSLog.hpp \
	include/Gates/DCSNot.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSNand.o: src/Gates/DCSNand.cpp \
	include/Gates/DCSNand.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAnd6.o: src/Gates/DCSAnd6.cpp \
	include/Gates/DCSAnd6.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Gates/DCSAnd6.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAnd.o: src/Gates/DCSAnd.cpp \
	include/Gates/DCSAnd.hpp \
	include/DCSCommon.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSOr.o: src/Gates/DCSOr.cpp \
	include/Gates/DCSOr.hpp \
	include/DCSCommon.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAnd4.o: src/Gates/DCSAnd4.cpp \
	include/Gates/DCSAnd4.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSNor3.o: src/Gates/DCSNor3.cpp \
	include/Gates/DCSNor3.hpp \
	include/DCSCommon.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAnd3.o: src/Gates/DCSAnd3.cpp \
	include/Gates/DCSAnd3.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSXor.o: src/Gates/DCSXor.cpp \
	include/Gates/DCSXor.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSMux2To1.o: src/Muxes-Demuxes/DCSMux2To1.cpp \
	include/Muxes-Demuxes/DCSMux2To1.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSTriStateBuffer8Bits.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSEngine.o: src/Core/DCSEngine.cpp \
	include/Core/DCSEngine.hpp \
	include/DCSCommon.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Connections/DCSInput.hpp \
	include/DCSInstructionSet.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp \
	include/Memory/DCSRam16x8.hpp \
	include/Memory/DCSRam256x16.hpp \
	include/Core/DCSTimer.hpp \
	include/Gates/DCSUnitDelay.hpp \
	include/Connections/DCSWire.hpp \
	include/DCSInstructionSet.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp \
	include/Memory/DCSRam16x8.hpp \
	include/Connections/DCSTriStateBuffer8Bits.hpp \
	include/Counters/DCSUpCounterWithLoadAndAsyncSR.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSLog.o: src/Core/DCSLog.cpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSTimer.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSTimer.o: src/Core/DCSTimer.cpp \
	include/Core/DCSTimer.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRegister8BitsWithEnable.o: src/Memory/DCSRegister8BitsWithEnable.cpp \
	include/Memory/DCSRegister8BitsWithEnable.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRegister4Bits.o: src/Memory/DCSRegister4Bits.cpp \
	include/Memory/DCSRegister4Bits.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRegister1Bit.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRam256x16.o: src/Memory/DCSRam256x16.cpp \
	include/Memory/DCSRam256x16.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRegister16BitsWithEnable.hpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRegister1Bit.o: src/Memory/DCSRegister1Bit.cpp \
	include/Memory/DCSRegister1Bit.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRam16x8.o: src/Memory/DCSRam16x8.cpp \
	include/Memory/DCSRam16x8.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/Memory/DCSRegister8BitsWithEnable.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp \
	include/Memory/DCSRam16x8.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRegister1BitWithEnable.o: src/Memory/DCSRegister1BitWithEnable.cpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRegister16BitsWithEnable.o: src/Memory/DCSRegister16BitsWithEnable.cpp \
	include/Memory/DCSRegister16BitsWithEnable.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRegister8Bits.o: src/Memory/DCSRegister8Bits.cpp \
	include/Memory/DCSRegister8Bits.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRegister1Bit.hpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSSRLatch.o: src/Latches/DCSSRLatch.cpp \
	include/Latches/DCSSRLatch.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSDFlipFlop.o: src/Latches/DCSDFlipFlop.cpp \
	include/Latches/DCSDFlipFlop.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSDLatch.o: src/Latches/DCSDLatch.cpp \
	include/Latches/DCSDLatch.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/prj-countByThrees.o: src/Projects/prj-countByThrees.cpp \
	include/Projects/prj-countByThrees.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/prj-fastZeroFlagProgram.o: src/Projects/prj-fastZeroFlagProgram.cpp \
	include/Projects/prj-fastZeroFlagProgram.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/prj-FastControlUnit.o: src/Projects/prj-FastControlUnit.cpp \
	include/Projects/prj-countByThrees.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/prj-NoCUComputer.o: src/Projects/prj-NoCUComputer.cpp \
	include/Projects/prj-NoCUComputer.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSClockSignal.o: src/Signals/DCSClockSignal.cpp \
	include/Signals/DCSClockSignal.hpp \
	include/Signals/DCSArbitrarySignal.hpp \
	include/Core/DCSEngine.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSArbitrarySignal.o: src/Signals/DCSArbitrarySignal.cpp \
	include/Signals/DCSArbitrarySignal.hpp \
	include/Core/DCSEngine.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSDisplayNBits.o: src/Displays/DCSDisplayNBits.cpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSEngine.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSNode.o: src/Connections/DCSNode.cpp \
	include/Connections/DCSNode.hpp \
	include/Connections/DCSWire.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSWire.o: src/Connections/DCSWire.cpp \
	include/Connections/DCSWire.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSTriStateBuffer.o: src/Connections/DCSTriStateBuffer.cpp \
	include/Connections/DCSTriStateBuffer.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSNode.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSOutput.o: src/Connections/DCSOutput.cpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSInput.o: src/Connections/DCSInput.cpp \
	include/Connections/DCSInput.hpp \
	include/Signals/DCSClockSignal.hpp \
	include/Core/DCSEngine.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSTriStateBuffer8Bits.o: src/Connections/DCSTriStateBuffer8Bits.cpp \
	include/Connections/DCSTriStateBuffer8Bits.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSControlUnit4Bits.o: src/ControlUnits/DCSControlUnit4Bits.cpp \
	include/ControlUnits/DCSControlUnit4Bits.hpp \
	include/Gates/DCSAnd3.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Memory/DCSRam256x16.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSControlUnit5Bits.o: src/ControlUnits/DCSControlUnit5Bits.cpp \
	include/ControlUnits/DCSControlUnit5Bits.hpp \
	include/Gates/DCSAnd3.hpp \
	include/Core/DCSLog.hpp \
	include/Decoders/DCSPLD8In16Out.hpp \
	include/Memory/DCSRam256x16.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSPLD8In16Out.o: src/Decoders/DCSPLD8In16Out.cpp \
	include/Decoders/DCSPLD8In16Out.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAddressDecoder8Bits.o: src/Decoders/DCSAddressDecoder8Bits.cpp \
	include/Decoders/DCSAddressDecoder8Bits.hpp \
	include/Gates/DCSAnd8.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Decoders/DCSAddressDecoder8Bits.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSAddressDecoder4Bits.o: src/Decoders/DCSAddressDecoder4Bits.cpp \
	include/Decoders/DCSAddressDecoder4Bits.hpp \
	include/Gates/DCSAnd4.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Decoders/DCSAddressDecoder4Bits.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSALU.o: src/Arithmetic/DCSALU.cpp \
	include/Arithmetic/DCSALU.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Arithmetic/DCSALU.hpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSRippleAdder8Bits.o: src/Arithmetic/DCSRippleAdder8Bits.cpp \
	include/Arithmetic/DCSRippleAdder8Bits.hpp \
	include/DCSCommon.hpp \
	include/Arithmetic/DCSFullAdder.hpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSFullAdder.o: src/Arithmetic/DCSFullAdder.cpp \
	include/Arithmetic/DCSFullAdder.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSClockDivider.o: src/Counters/DCSClockDivider.cpp \
	include/Counters/DCSClockDivider.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSUpCounterWithLoadAndAsyncSR.o: src/Counters/DCSUpCounterWithLoadAndAsyncSR.cpp \
	include/Counters/DCSUpCounterWithLoadAndAsyncSR.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/main-test.o: src/main-test.cpp \
	include/DCSCommon.hpp \
	include/Arithmetic/DCSALU.hpp \
	include/Decoders/DCSAddressDecoder4Bits.hpp \
	include/Decoders/DCSAddressDecoder8Bits.hpp \
	include/Gates/DCSAnd6.hpp \
	include/Counters/DCSClockDivider.hpp \
	include/Base/DCSComponentArray.hpp \
	include/ControlUnits/DCSControlUnit4Bits.hpp \
	include/Latches/DCSDFlipFlop.hpp \
	include/Latches/DCSDLatch.hpp \
	include/Latches-async-SR/DCSDLatchAsyncSR.hpp \
	include/Displays/DCSDisplayNBits.hpp \
	include/Core/DCSEngine.hpp \
	include/Arithmetic/DCSFullAdder.hpp \
	include/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.hpp \
	include/Core/DCSLog.hpp \
	include/Muxes-Demuxes/DCSMux2To1.hpp \
	include/Gates/DCSNand3.hpp \
	include/Gates/DCSNor3.hpp \
	include/Gates/DCSNot.hpp \
	include/Gates/DCSOr.hpp \
	include/Memory/DCSRam16x8.hpp \
	include/Memory/DCSRam256x16.hpp \
	include/Memory/DCSRegister16BitsWithEnable.hpp \
	include/Memory/DCSRegister1Bit.hpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/Memory/DCSRegister8Bits.hpp \
	include/Memory/DCSRegister8BitsWithEnable.hpp \
	include/Arithmetic/DCSRippleAdder8Bits.hpp \
	include/Latches/DCSSRLatch.hpp \
	include/Core/DCSTimer.hpp \
	include/Connections/DCSTriStateBuffer.hpp \
	include/Gates/DCSUnitDelay.hpp \
	include/Counters/DCSUpCounterWithLoadAndAsyncSR.hpp \
	include/Gates/DCSXor.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/main.o: src/main.cpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Projects/prj-FastControlUnit.hpp \
	include/Projects/prj-NoCUComputer.hpp \
	include/Projects/prj-countByThrees.hpp \
	include/Projects/prj-fastZeroFlagProgram.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSComponent.o: src/Base/DCSComponent.cpp \
	include/Base/DCSComponent.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSWire.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSComponentArray.o: src/Base/DCSComponentArray.cpp \
	include/Base/DCSComponentArray.hpp \
	include/Gates/DCSAnd.hpp \
	include/Gates/DCSAnd3.hpp \
	include/Gates/DCSAnd4.hpp \
	include/Gates/DCSAnd6.hpp \
	include/Gates/DCSAnd8.hpp \
	include/Counters/DCSClockDivider.hpp \
	include/DCSCommon.hpp \
	include/Latches/DCSDFlipFlop.hpp \
	include/Latches-async-SR/DCSDFlipFlopAsyncSR.hpp \
	include/Latches/DCSDLatch.hpp \
	include/Latches-async-SR/DCSDLatchAsyncSR.hpp \
	include/Arithmetic/DCSFullAdder.hpp \
	include/Connections/DCSInput.hpp \
	include/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.hpp \
	include/Core/DCSLog.hpp \
	include/Gates/DCSNand.hpp \
	include/Gates/DCSNand3.hpp \
	include/Connections/DCSNode.hpp \
	include/Gates/DCSNor.hpp \
	include/Gates/DCSNor3.hpp \
	include/Gates/DCSNot.hpp \
	include/Gates/DCSOr.hpp \
	include/Connections/DCSOutput.hpp \
	include/Memory/DCSRegister16BitsWithEnable.hpp \
	include/Memory/DCSRegister1Bit.hpp \
	include/Memory/DCSRegister1BitWithEnable.hpp \
	include/Memory/DCSRegister8Bits.hpp \
	include/Memory/DCSRegister8BitsWithEnable.hpp \
	include/Latches/DCSSRLatch.hpp \
	include/Connections/DCSTriStateBuffer.hpp \
	include/Connections/DCSTriStateBuffer8Bits.hpp \
	include/Gates/DCSUnitDelay.hpp \
	include/Gates/DCSXor.hpp \
	include/Gates/DCSAnd.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSDFlipFlopAsyncSR.o: src/Latches-async-SR/DCSDFlipFlopAsyncSR.cpp \
	include/Latches-async-SR/DCSDFlipFlopAsyncSR.hpp \
	include/Core/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSDLatchAsyncSR.o: src/Latches-async-SR/DCSDLatchAsyncSR.cpp \
	include/Latches-async-SR/DCSDLatchAsyncSR.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Latches-async-SR/DCSDLatchAsyncSR.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Core/DCSLog.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@


build/DCSJKLatchMasterSlaveAsyncSR.o: src/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.cpp \
	include/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.hpp \
	include/DCSCommon.hpp \
	include/Core/DCSLog.hpp \
	include/Base/DCSComponentArray.hpp \
	include/Core/DCSEngine.hpp \
	include/Connections/DCSInput.hpp \
	include/Connections/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -O$(OPT) -c $< -o $@

