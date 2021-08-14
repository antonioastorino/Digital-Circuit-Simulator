# Makefile auto generated using custom generator
OBJCFLAGS=
CPPFLAGS=-Wall -Wextra -g -std=c++1z
CFLAGS=
MAINFLAGS=-Wall -Wextra -g -std=c++1z
BD=/Users/antonio/Projects/DCS/bin/..
OPT ?= 0
LIB=-lc++ -pthread
INC= -Iinclude \

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
	make -C "$(BD)" build/dcs-test; \
	else \
	[ `grep -c '^#define TEST 1' "$(BD)"/include/DCSCommon.hpp` -eq 1 ] && \
	sed -i.bak 's/^#define TEST 1/#define TEST 0/g' "$(BD)"/include/DCSCommon.hpp; \
	[ `grep -c '^#define MEM_ANALYSIS 1' "$(BD)"/include/DCSCommon.hpp` -eq 1 ] && \
	sed -i.bak 's/^#define MEM_ANALYSIS 1/#define MEM_ANALYSIS 0/g' "$(BD)"/include/DCSCommon.hpp; \
	make -C "$(BD)" build/dcs; \
	fi

build/dcs:\
	build/DCSControlUnit4Bits.o \
	build/DCSControlUnit5Bits.o \
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
	build/DCSMux2to1.o \
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
	build/main.o \
	build/prj-NoCUComputer.o \
	build/DCSClockSignal.o \
	build/DCSArbitrarySignal.o \
	build/DCSDisplayNBits.o \
	build/test-Register1BitWithEnable.o \
	build/test-TriStateBuffer.o \
	build/test-Register8Bits.o \
	build/test-UnitDelay.o \
	build/test-Register8BitsWithEnable.o \
	build/test-NotLoop.o \
	build/test-Ram256x16.o \
	build/test-SRLatch.o \
	build/test-Nor3.o \
	build/test-Register16BitsWithEnable.o \
	build/test-UpCounter4Bits.o \
	build/test-UpCounter.o \
	build/test-Xor.o \
	build/test-Register1Bit.o \
	build/test-RippleAdder.o \
	build/test-Or.o \
	build/test-RisingEdgeDetector.o \
	build/DCSComponent.o \
	build/DCSComponentArray.o \
	build/DCSNode.o \
	build/DCSWire.o \
	build/DCSTriStateBuffer.o \
	build/DCSOutput.o \
	build/DCSInput.o \
	build/DCSTriStateBuffer8Bits.o \
	build/DCSPLD8In16Out.o \
	build/DCSAddressDecoder8Bits.o \
	build/DCSAddressDecoder4Bits.o \
	build/DCSALU.o \
	build/DCSRippleAdder8Bits.o \
	build/DCSFullAdder.o \
	build/DCSClockDivider.o \
	build/DCSUpCounterWithLoadAndAsyncSR.o \
	build/DCSDFlipFlopAsyncSR.o \
	build/DCSDLatchAsyncSR.o \
	build/DCSJKLatchMasterSlaveAsyncSR.o 
	clang $(LIB) $(MAINFLAGS) -O$(OPT) $(INC) $(FRAMEWORKS) $^ -o $@

build/dcs-test:\
	build/DCSControlUnit4Bits.o \
	build/DCSControlUnit5Bits.o \
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
	build/DCSMux2to1.o \
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
	build/test-Register1BitWithEnable.o \
	build/test-TriStateBuffer.o \
	build/test-Register8Bits.o \
	build/test-UnitDelay.o \
	build/test-Register8BitsWithEnable.o \
	build/test-NotLoop.o \
	build/test-Ram256x16.o \
	build/test-SRLatch.o \
	build/test-Nor3.o \
	build/test-Register16BitsWithEnable.o \
	build/test-UpCounter4Bits.o \
	build/test-UpCounter.o \
	build/test-Xor.o \
	build/test-Register1Bit.o \
	build/test-RippleAdder.o \
	build/main-test.o \
	build/test-Or.o \
	build/test-RisingEdgeDetector.o \
	build/DCSComponent.o \
	build/DCSComponentArray.o \
	build/DCSNode.o \
	build/DCSWire.o \
	build/DCSTriStateBuffer.o \
	build/DCSOutput.o \
	build/DCSInput.o \
	build/DCSTriStateBuffer8Bits.o \
	build/DCSPLD8In16Out.o \
	build/DCSAddressDecoder8Bits.o \
	build/DCSAddressDecoder4Bits.o \
	build/DCSALU.o \
	build/DCSRippleAdder8Bits.o \
	build/DCSFullAdder.o \
	build/DCSClockDivider.o \
	build/DCSUpCounterWithLoadAndAsyncSR.o \
	build/DCSDFlipFlopAsyncSR.o \
	build/DCSDLatchAsyncSR.o \
	build/DCSJKLatchMasterSlaveAsyncSR.o 
	clang $(LIB) $(MAINFLAGS) -O$(OPT) $(INC) $(FRAMEWORKS) $^ -o $@

build/DCSControlUnit4Bits.o: src/ControlUnit/DCSControlUnit4Bits.cpp \
	include/DCSControlUnit4Bits.hpp \
	include/DCSAnd3.hpp \
	include/DCSCommon.hpp \
	include/DCSLog.hpp \
	include/DCSRam256x16.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSControlUnit5Bits.o: src/ControlUnit/DCSControlUnit5Bits.cpp \
	include/DCSControlUnit5Bits.hpp \
	include/DCSAnd3.hpp \
	include/DCSLog.hpp \
	include/DCSRam256x16.hpp \
	include/DCSPLD8In16Out.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSNand3.o: src/Gates/DCSNand3.cpp \
	include/DCSNand3.hpp \
	include/DCSCommon.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAnd8.o: src/Gates/DCSAnd8.cpp \
	include/DCSAnd8.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSNor.o: src/Gates/DCSNor.cpp \
	include/DCSNor.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSNot.o: src/Gates/DCSNot.cpp \
	include/DCSNot.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSUnitDelay.o: src/Gates/DCSUnitDelay.cpp \
	include/DCSUnitDelay.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSNand.o: src/Gates/DCSNand.cpp \
	include/DCSNand.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAnd6.o: src/Gates/DCSAnd6.cpp \
	include/DCSAnd6.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSAnd6.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAnd.o: src/Gates/DCSAnd.cpp \
	include/DCSAnd.hpp \
	include/DCSCommon.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSOr.o: src/Gates/DCSOr.cpp \
	include/DCSOr.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAnd4.o: src/Gates/DCSAnd4.cpp \
	include/DCSAnd4.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSNor3.o: src/Gates/DCSNor3.cpp \
	include/DCSNor3.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAnd3.o: src/Gates/DCSAnd3.cpp \
	include/DCSAnd3.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSXor.o: src/Gates/DCSXor.cpp \
	include/DCSXor.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSMux2to1.o: src/Muxes-Demuxes/DCSMux2to1.cpp \
	include/DCSMux2to1.hpp \
	include/DCSCommon.hpp \
	include/DCSLog.hpp \
	include/DCSTriStateBuffer8Bits.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSEngine.o: src/Core/DCSEngine.cpp \
	include/DCSEngine.hpp \
	include/DCSComponentArray.hpp \
	include/DCSInput.hpp \
	include/DCSInstructionSet.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp \
	include/DCSRam16x8.hpp \
	include/DCSRam256x16.hpp \
	include/DCSTimer.hpp \
	include/DCSUnitDelay.hpp \
	include/DCSWire.hpp \
	include/DCSCommon.hpp \
	include/DCSInstructionSet.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp \
	include/DCSRam16x8.hpp \
	include/DCSTriStateBuffer8Bits.hpp \
	include/DCSUpCounterWithLoadAndAsyncSR.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSLog.o: src/Core/DCSLog.cpp \
	include/DCSLog.hpp \
	include/DCSTimer.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSTimer.o: src/Core/DCSTimer.cpp \
	include/DCSTimer.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRegister8BitsWithEnable.o: src/Memory/DCSRegister8BitsWithEnable.cpp \
	include/DCSRegister8BitsWithEnable.hpp \
	include/DCSLog.hpp \
	include/DCSRegister1BitWithEnable.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRegister4Bits.o: src/Memory/DCSRegister4Bits.cpp \
	include/DCSRegister4Bits.hpp \
	include/DCSLog.hpp \
	include/DCSRegister1Bit.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRam256x16.o: src/Memory/DCSRam256x16.cpp \
	include/DCSRam256x16.hpp \
	include/DCSLog.hpp \
	include/DCSRegister1BitWithEnable.hpp \
	include/DCSRegister16BitsWithEnable.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRegister1Bit.o: src/Memory/DCSRegister1Bit.cpp \
	include/DCSRegister1Bit.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRam16x8.o: src/Memory/DCSRam16x8.cpp \
	include/DCSRam16x8.hpp \
	include/DCSLog.hpp \
	include/DCSRegister1BitWithEnable.hpp \
	include/DCSRegister8BitsWithEnable.hpp \
	include/DCSCommon.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp \
	include/DCSRam16x8.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRegister1BitWithEnable.o: src/Memory/DCSRegister1BitWithEnable.cpp \
	include/DCSRegister1BitWithEnable.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRegister16BitsWithEnable.o: src/Memory/DCSRegister16BitsWithEnable.cpp \
	include/DCSRegister16BitsWithEnable.hpp \
	include/DCSLog.hpp \
	include/DCSRegister1BitWithEnable.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRegister8Bits.o: src/Memory/DCSRegister8Bits.cpp \
	include/DCSRegister8Bits.hpp \
	include/DCSLog.hpp \
	include/DCSRegister1Bit.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSSRLatch.o: src/Latches/DCSSRLatch.cpp \
	include/DCSSRLatch.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSDFlipFlop.o: src/Latches/DCSDFlipFlop.cpp \
	include/DCSDFlipFlop.hpp \
	include/DCSCommon.hpp \
	include/DCSLog.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSDLatch.o: src/Latches/DCSDLatch.cpp \
	include/DCSDLatch.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/prj-countByThrees.o: src/Projects/prj-countByThrees.cpp \
	src/Projects/prj-countByThrees.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/prj-fastZeroFlagProgram.o: src/Projects/prj-fastZeroFlagProgram.cpp \
	src/Projects/prj-fastZeroFlagProgram.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/prj-FastControlUnit.o: src/Projects/prj-FastControlUnit.cpp \
	src/Projects/prj-countByThrees.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/main.o: src/Projects/main.cpp \
	include/DCSLog.hpp \
	src/Projects/prj-FastControlUnit.hpp \
	src/Projects/prj-countByThrees.hpp \
	src/Projects/prj-NoCUComputer.hpp \
	src/Projects/prj-fastZeroFlagProgram.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/prj-NoCUComputer.o: src/Projects/prj-NoCUComputer.cpp \
	src/Projects/prj-NoCUComputer.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSClockSignal.o: src/Signals/DCSClockSignal.cpp \
	include/DCSArbitrarySignal.hpp \
	include/DCSClockSignal.hpp \
	include/DCSEngine.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSArbitrarySignal.o: src/Signals/DCSArbitrarySignal.cpp \
	include/DCSArbitrarySignal.hpp \
	include/DCSEngine.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSDisplayNBits.o: src/Displays/DCSDisplayNBits.cpp \
	include/DCSDisplayNBits.hpp \
	include/DCSEngine.hpp \
	include/DCSCommon.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Register1BitWithEnable.o: src/Tests/test-Register1BitWithEnable.cpp \
	src/Tests/test-Register1BitWithEnable.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-TriStateBuffer.o: src/Tests/test-TriStateBuffer.cpp \
	src/Tests/test-TriStateBuffer.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Register8Bits.o: src/Tests/test-Register8Bits.cpp \
	src/Tests/test-Register8Bits.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-UnitDelay.o: src/Tests/test-UnitDelay.cpp \
	src/Tests/test-UnitDelay.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Register8BitsWithEnable.o: src/Tests/test-Register8BitsWithEnable.cpp \
	src/Tests/test-Register8BitsWithEnable.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-NotLoop.o: src/Tests/test-NotLoop.cpp \
	src/Tests/test-NotLoop.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Ram256x16.o: src/Tests/test-Ram256x16.cpp \
	src/Tests/test-Ram256x16.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-SRLatch.o: src/Tests/test-SRLatch.cpp \
	src/Tests/test-SRLatch.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Nor3.o: src/Tests/test-Nor3.cpp \
	src/Tests/test-Nor3.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Register16BitsWithEnable.o: src/Tests/test-Register16BitsWithEnable.cpp \
	src/Tests/test-Register16BitsWithEnable.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-UpCounter4Bits.o: src/Tests/test-UpCounter4Bits.cpp \
	src/Tests/test-UpCounter4Bits.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-UpCounter.o: src/Tests/test-UpCounter.cpp \
	src/Tests/test-UpCounter.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Xor.o: src/Tests/test-Xor.cpp \
	src/Tests/test-Xor.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Register1Bit.o: src/Tests/test-Register1Bit.cpp \
	src/Tests/test-Register1Bit.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-RippleAdder.o: src/Tests/test-RippleAdder.cpp \
	src/Tests/test-RippleAdder.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/main-test.o: src/Tests/main-test.cpp \
	include/DCSALU.hpp \
	include/DCSAddressDecoder4Bits.hpp \
	include/DCSAddressDecoder8Bits.hpp \
	include/DCSAnd6.hpp \
	include/DCSComponentArray.hpp \
	include/DCSControlUnit4Bits.hpp \
	include/DCSDFlipFlop.hpp \
	include/DCSDisplayNBits.hpp \
	include/DCSEngine.hpp \
	include/DCSLog.hpp \
	include/DCSRam16x8.hpp \
	include/DCSTimer.hpp \
	include/DCSDLatch.hpp \
	include/DCSDLatchAsyncSR.hpp \
	include/DCSClockDivider.hpp \
	include/DCSFullAdder.hpp \
	include/DCSJKLatchMasterSlaveAsyncSR.hpp \
	 \
	include/DCSNand3.hpp \
	src/Tests/test-Nor3.hpp \
	src/Tests/test-NotLoop.hpp \
	src/Tests/test-Or.hpp \
	src/Tests/test-Ram256x16.hpp \
	src/Tests/test-Register16BitsWithEnable.hpp \
	src/Tests/test-Register1Bit.hpp \
	src/Tests/test-Register1BitWithEnable.hpp \
	src/Tests/test-Register8Bits.hpp \
	src/Tests/test-Register8BitsWithEnable.hpp \
	src/Tests/test-RippleAdder.hpp \
	src/Tests/test-RisingEdgeDetector.hpp \
	src/Tests/test-SRLatch.hpp \
	src/Tests/test-TriStateBuffer.hpp \
	src/Tests/test-UnitDelay.hpp \
	src/Tests/test-UpCounter.hpp \
	src/Tests/test-UpCounter4Bits.hpp \
	src/Tests/test-Xor.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-Or.o: src/Tests/test-Or.cpp \
	src/Tests/test-Or.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/test-RisingEdgeDetector.o: src/Tests/test-RisingEdgeDetector.cpp \
	src/Tests/test-RisingEdgeDetector.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSComponent.o: src/Basic/DCSComponent.cpp \
	include/DCSComponent.hpp \
	include/DCSEngine.hpp \
	include/DCSWire.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSComponentArray.o: src/Basic/DCSComponentArray.cpp \
	include/DCSComponentArray.hpp \
	include/DCSAnd.hpp \
	include/DCSAnd3.hpp \
	include/DCSAnd4.hpp \
	include/DCSAnd6.hpp \
	include/DCSAnd8.hpp \
	include/DCSClockDivider.hpp \
	include/DCSDFlipFlop.hpp \
	include/DCSDFlipFlopAsyncSR.hpp \
	include/DCSDLatch.hpp \
	include/DCSDLatchAsyncSR.hpp \
	include/DCSFullAdder.hpp \
	include/DCSInput.hpp \
	include/DCSJKLatchMasterSlaveAsyncSR.hpp \
	include/DCSLog.hpp \
	include/DCSNand.hpp \
	include/DCSNand3.hpp \
	include/DCSNode.hpp \
	include/DCSNor.hpp \
	include/DCSNor3.hpp \
	include/DCSNot.hpp \
	include/DCSOr.hpp \
	include/DCSOutput.hpp \
	include/DCSRegister16BitsWithEnable.hpp \
	include/DCSRegister1Bit.hpp \
	include/DCSRegister1BitWithEnable.hpp \
	include/DCSRegister8Bits.hpp \
	include/DCSRegister8BitsWithEnable.hpp \
	include/DCSSRLatch.hpp \
	include/DCSTriStateBuffer.hpp \
	include/DCSTriStateBuffer8Bits.hpp \
	include/DCSUnitDelay.hpp \
	include/DCSXor.hpp \
	include/DCSCommon.hpp \
	include/DCSAnd.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSNode.o: src/Connections/DCSNode.cpp \
	include/DCSNode.hpp \
	include/DCSWire.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSWire.o: src/Connections/DCSWire.cpp \
	include/DCSWire.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSTriStateBuffer.o: src/Connections/DCSTriStateBuffer.cpp \
	include/DCSTriStateBuffer.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSOutput.o: src/Connections/DCSOutput.cpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSInput.o: src/Connections/DCSInput.cpp \
	include/DCSInput.hpp \
	include/DCSClockSignal.hpp \
	include/DCSEngine.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSTriStateBuffer8Bits.o: src/Connections/DCSTriStateBuffer8Bits.cpp \
	include/DCSTriStateBuffer8Bits.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSPLD8In16Out.o: src/Decoders/DCSPLD8In16Out.cpp \
	include/DCSPLD8In16Out.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAddressDecoder8Bits.o: src/Decoders/DCSAddressDecoder8Bits.cpp \
	include/DCSAddressDecoder8Bits.hpp \
	include/DCSAnd8.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSAddressDecoder8Bits.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSAddressDecoder4Bits.o: src/Decoders/DCSAddressDecoder4Bits.cpp \
	include/DCSAddressDecoder4Bits.hpp \
	include/DCSAnd4.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSAddressDecoder4Bits.hpp \
	include/DCSComponentArray.hpp \
	include/DCSDisplayNBits.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSALU.o: src/Arithmetic/DCSALU.cpp \
	include/DCSALU.hpp \
	include/DCSCommon.hpp \
	include/DCSLog.hpp \
	include/DCSALU.hpp \
	include/DCSDisplayNBits.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSRippleAdder8Bits.o: src/Arithmetic/DCSRippleAdder8Bits.cpp \
	include/DCSRippleAdder8Bits.hpp \
	include/DCSFullAdder.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSFullAdder.o: src/Arithmetic/DCSFullAdder.cpp \
	include/DCSFullAdder.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSClockDivider.o: src/Counters/DCSClockDivider.cpp \
	include/DCSClockDivider.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSUpCounterWithLoadAndAsyncSR.o: src/Counters/DCSUpCounterWithLoadAndAsyncSR.cpp \
	include/DCSUpCounterWithLoadAndAsyncSR.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSDFlipFlopAsyncSR.o: src/Latches-async-SR/DCSDFlipFlopAsyncSR.cpp \
	include/DCSDFlipFlopAsyncSR.hpp \
	include/DCSLog.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSDLatchAsyncSR.o: src/Latches-async-SR/DCSDLatchAsyncSR.cpp \
	include/DCSDLatchAsyncSR.hpp \
	include/DCSLog.hpp \
	include/DCSCommon.hpp \
	include/DCSComponentArray.hpp \
	include/DCSDLatchAsyncSR.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSLog.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@


build/DCSJKLatchMasterSlaveAsyncSR.o: src/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.cpp \
	include/DCSJKLatchMasterSlaveAsyncSR.hpp \
	include/DCSCommon.hpp \
	include/DCSLog.hpp \
	include/DCSComponentArray.hpp \
	include/DCSEngine.hpp \
	include/DCSInput.hpp \
	include/DCSOutput.hpp 
	g++ $(INC) $(CPPFLAGS) -c $< -o $@

