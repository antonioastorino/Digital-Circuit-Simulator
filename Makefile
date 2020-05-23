# Makefile auto generated using custom generator

CFLAGS=-c -Wextra -std=c++17 -O$(OPT) -g
CC=g++
INC= -I.//include\
 -I.//src/Projects\
 -I.//src/Tests\

.PHONY: all clean cleanall check-directory make-opt check-opt-value

all: check-directory

check-directory:
	@[ -d "build/objects" ] || mkdir -p build/objects
	@[ -d "build" ] || mkdir -p build
	@make check-opt-value OPT=$(OPT)

check-opt-value:
	@[ "$(OPT)" == "" ] && make make-opt OPT=0 || make make-opt OPT=$(OPT)

make-opt:
	@if [ ! -f "build/.out-$(OPT)" ]; then \
		rm -rf build/*; \
		mkdir -p build/objects; \
		touch build/.out-$(OPT); \
	fi
	@make build/test-out-$(OPT) OPT=$(OPT)
	@make build/prj-out-$(OPT) OPT=$(OPT)

build/test-out-$(OPT): build/objects/DCSControlUnit4Bits.o build/objects/DCSControlUnit5Bits.o build/objects/DCSNand3.o build/objects/DCSAnd8.o build/objects/DCSNor.o build/objects/DCSNot.o build/objects/DCSUnitDelay.o build/objects/DCSNand.o build/objects/DCSAnd6.o build/objects/DCSAnd.o build/objects/DCSOr.o build/objects/DCSAnd4.o build/objects/DCSNor3.o build/objects/DCSAnd3.o build/objects/DCSXor.o build/objects/DCSMux2to1.o build/objects/DCSEngine.o build/objects/DCSLog.o build/objects/DCSTimer.o build/objects/DCSRegister8BitsWithEnable.o build/objects/DCSRegister4Bits.o build/objects/DCSRam256x16.o build/objects/DCSRegister1Bit.o build/objects/DCSRam16x8.o build/objects/DCSRegister1BitWithEnable.o build/objects/DCSRegister16BitsWithEnable.o build/objects/DCSRegister8Bits.o build/objects/DCSSRLatch.o build/objects/DCSDFlipFlop.o build/objects/DCSDLatch.o build/objects/DCSClockSignal.o build/objects/DCSArbitrarySignal.o build/objects/DCSDisplayNBits.o build/objects/test-Register1BitWithEnable.o build/objects/test-BitStreamSignal.o build/objects/test-FullAdder.o build/objects/test-ControlUnit.o build/objects/test-TriStateBuffer.o build/objects/test-ALU.o build/objects/test-DLatch.o build/objects/test-Ram.o build/objects/test-DLatchAsyncSR.o build/objects/test-Divider.o build/objects/test-Register8Bits.o build/objects/test-Nand3.o build/objects/test-UnitDelay.o build/objects/test-Register8BitsWithEnable.o build/objects/test-NotLoop.o build/objects/test-DFlipFlop.o build/objects/test-And6.o build/objects/test-Ram256x16.o build/objects/test-AddressDecoder32Bits.o build/objects/test-AddressDecoder.o build/objects/test-MemoryProgrammer.o build/objects/test-SRLatch.o build/objects/test-AndArray.o build/objects/test-Nor3.o build/objects/test-Register16BitsWithEnable.o build/objects/test-Mux2To1.o build/objects/test-UpCounter4Bits.o build/objects/test-UpCounter.o build/objects/test-all.o build/objects/test-Display.o build/objects/test-Xor.o build/objects/test-Register1Bit.o build/objects/test-RippleAdder.o build/objects/test-Or.o build/objects/test-RisingEdgeDetector.o build/objects/test-JKMasterSlave.o build/objects/DCSComponent.o build/objects/DCSComponentArray.o build/objects/DCSNode.o build/objects/DCSWire.o build/objects/DCSTriStateBuffer.o build/objects/DCSOutput.o build/objects/DCSInput.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSPLD8In16Out.o build/objects/DCSAddressDecoder8Bits.o build/objects/DCSAddressDecoder4Bits.o build/objects/DCSALU.o build/objects/DCSRippleAdder8Bits.o build/objects/DCSFullAdder.o build/objects/DCSClockDivider.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSDFlipFlopAsyncSR.o build/objects/DCSDLatchAsyncSR.o build/objects/DCSJKLatchMasterSlaveAsyncSR.o
	$(CC) $(INC) -o $@ $^

build/prj-out-$(OPT): build/objects/DCSControlUnit4Bits.o build/objects/DCSControlUnit5Bits.o build/objects/DCSNand3.o build/objects/DCSAnd8.o build/objects/DCSNor.o build/objects/DCSNot.o build/objects/DCSUnitDelay.o build/objects/DCSNand.o build/objects/DCSAnd6.o build/objects/DCSAnd.o build/objects/DCSOr.o build/objects/DCSAnd4.o build/objects/DCSNor3.o build/objects/DCSAnd3.o build/objects/DCSXor.o build/objects/DCSMux2to1.o build/objects/DCSEngine.o build/objects/DCSLog.o build/objects/DCSTimer.o build/objects/DCSRegister8BitsWithEnable.o build/objects/DCSRegister4Bits.o build/objects/DCSRam256x16.o build/objects/DCSRegister1Bit.o build/objects/DCSRam16x8.o build/objects/DCSRegister1BitWithEnable.o build/objects/DCSRegister16BitsWithEnable.o build/objects/DCSRegister8Bits.o build/objects/DCSSRLatch.o build/objects/DCSDFlipFlop.o build/objects/DCSDLatch.o build/objects/prj-all.o build/objects/prj-FirstProgram.o build/objects/prj-fastZeroFlagProgram.o build/objects/prj-FastControlUnit.o build/objects/prj-NoCUComputer.o build/objects/DCSClockSignal.o build/objects/DCSArbitrarySignal.o build/objects/DCSDisplayNBits.o build/objects/DCSComponent.o build/objects/DCSComponentArray.o build/objects/DCSNode.o build/objects/DCSWire.o build/objects/DCSTriStateBuffer.o build/objects/DCSOutput.o build/objects/DCSInput.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSPLD8In16Out.o build/objects/DCSAddressDecoder8Bits.o build/objects/DCSAddressDecoder4Bits.o build/objects/DCSALU.o build/objects/DCSRippleAdder8Bits.o build/objects/DCSFullAdder.o build/objects/DCSClockDivider.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSDFlipFlopAsyncSR.o build/objects/DCSDLatchAsyncSR.o build/objects/DCSJKLatchMasterSlaveAsyncSR.o
	$(CC) $(INC) -o $@ $^

build/objects/DCSControlUnit4Bits.o: .//src/ControlUnit/DCSControlUnit4Bits.cpp .//include/DCSControlUnit4Bits.hpp .//include/DCSAnd3.hpp .//include/DCSLog.hpp .//include/DCSRam256x16.hpp build/objects/DCSComponent.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSUnitDelay.o build/objects/DCSInput.o build/objects/DCSDisplayNBits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSControlUnit5Bits.o: .//src/ControlUnit/DCSControlUnit5Bits.cpp .//include/DCSControlUnit5Bits.hpp .//include/DCSAnd3.hpp .//include/DCSLog.hpp .//include/DCSRam256x16.hpp .//include/DCSPLD8In16Out.hpp build/objects/DCSComponent.o build/objects/DCSDisplayNBits.o build/objects/DCSInput.o build/objects/DCSNode.o build/objects/DCSNot.o build/objects/DCSRegister8Bits.o build/objects/DCSUnitDelay.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNand3.o: .//src/Gates/DCSNand3.cpp .//include/DCSNand3.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd8.o: .//src/Gates/DCSAnd8.cpp .//include/DCSAnd8.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNor.o: .//src/Gates/DCSNor.cpp .//include/DCSNor.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNot.o: .//src/Gates/DCSNot.cpp .//include/DCSNot.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSUnitDelay.o: .//src/Gates/DCSUnitDelay.cpp .//include/DCSUnitDelay.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNand.o: .//src/Gates/DCSNand.cpp .//include/DCSNand.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd6.o: .//src/Gates/DCSAnd6.cpp .//include/DCSAnd6.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd.o: .//src/Gates/DCSAnd.cpp .//include/DCSAnd.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSOr.o: .//src/Gates/DCSOr.cpp .//include/DCSOr.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd4.o: .//src/Gates/DCSAnd4.cpp .//include/DCSAnd4.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNor3.o: .//src/Gates/DCSNor3.cpp .//include/DCSNor3.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd3.o: .//src/Gates/DCSAnd3.cpp .//include/DCSAnd3.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSXor.o: .//src/Gates/DCSXor.cpp .//include/DCSXor.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSMux2to1.o: .//src/Muxes-Demuxes/DCSMux2to1.cpp .//include/DCSMux2to1.hpp .//include/DCSLog.hpp .//include/DCSTriStateBuffer8Bits.hpp build/objects/DCSAnd.o build/objects/DCSNode.o build/objects/DCSNot.o build/objects/DCSOr.o build/objects/DCSUnitDelay.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSEngine.o: .//src/Core/DCSEngine.cpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp .//include/DCSInput.hpp .//include/DCSInstructionSet.hpp .//include/DCSLog.hpp .//include/DCSOutput.hpp .//include/DCSRam16x8.hpp .//include/DCSRam256x16.hpp .//include/DCSTimer.hpp .//include/DCSUnitDelay.hpp .//include/DCSWire.hpp build/objects/DCSDisplayNBits.o build/objects/DCSLog.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSLog.o: .//src/Core/DCSLog.cpp .//include/DCSLog.hpp .//include/DCSTimer.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSTimer.o: .//src/Core/DCSTimer.cpp .//include/DCSTimer.hpp .//include/DCSLog.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister8BitsWithEnable.o: .//src/Memory/DCSRegister8BitsWithEnable.cpp .//include/DCSRegister8BitsWithEnable.hpp .//include/DCSLog.hpp .//include/DCSRegister1BitWithEnable.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister4Bits.o: .//src/Memory/DCSRegister4Bits.cpp .//include/DCSRegister4Bits.hpp .//include/DCSLog.hpp .//include/DCSRegister1Bit.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRam256x16.o: .//src/Memory/DCSRam256x16.cpp .//include/DCSRam256x16.hpp .//include/DCSLog.hpp .//include/DCSRegister1BitWithEnable.hpp .//include/DCSRegister16BitsWithEnable.hpp build/objects/DCSAddressDecoder8Bits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister1Bit.o: .//src/Memory/DCSRegister1Bit.cpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp build/objects/DCSDFlipFlopAsyncSR.o build/objects/DCSOr.o build/objects/DCSTriStateBuffer.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRam16x8.o: .//src/Memory/DCSRam16x8.cpp .//include/DCSRam16x8.hpp .//include/DCSLog.hpp .//include/DCSRegister1BitWithEnable.hpp .//include/DCSRegister8BitsWithEnable.hpp build/objects/DCSAddressDecoder4Bits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister1BitWithEnable.o: .//src/Memory/DCSRegister1BitWithEnable.cpp .//include/DCSRegister1BitWithEnable.hpp .//include/DCSLog.hpp build/objects/DCSRegister1Bit.o build/objects/DCSTriStateBuffer.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister16BitsWithEnable.o: .//src/Memory/DCSRegister16BitsWithEnable.cpp .//include/DCSRegister16BitsWithEnable.hpp .//include/DCSLog.hpp .//include/DCSRegister1BitWithEnable.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister8Bits.o: .//src/Memory/DCSRegister8Bits.cpp .//include/DCSRegister8Bits.hpp .//include/DCSLog.hpp .//include/DCSRegister1Bit.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSSRLatch.o: .//src/Latches/DCSSRLatch.cpp .//include/DCSSRLatch.hpp .//include/DCSLog.hpp build/objects/DCSNor.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDFlipFlop.o: .//src/Latches/DCSDFlipFlop.cpp .//include/DCSDFlipFlop.hpp .//include/DCSLog.hpp build/objects/DCSDLatch.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDLatch.o: .//src/Latches/DCSDLatch.cpp .//include/DCSDLatch.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSNode.o build/objects/DCSNot.o build/objects/DCSSRLatch.o build/objects/DCSUnitDelay.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/prj-all.o: .//src/Projects/prj-all.cpp .//src/Projects/prj-FastControlUnit.hpp .//src/Projects/prj-fastZeroFlagProgram.hpp .//src/Projects/prj-FirstProgram.hpp .//src/Projects/prj-NoCUComputer.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/prj-FirstProgram.o: .//src/Projects/prj-FirstProgram.cpp .//src/Projects/prj-FirstProgram.hpp build/objects/DCSALU.o build/objects/DCSControlUnit4Bits.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRam16x8.o build/objects/DCSRam256x16.o build/objects/DCSRegister4Bits.o build/objects/DCSRegister8Bits.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSNot.o build/objects/DCSAnd.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/prj-fastZeroFlagProgram.o: .//src/Projects/prj-fastZeroFlagProgram.cpp .//src/Projects/prj-fastZeroFlagProgram.hpp build/objects/DCSALU.o build/objects/DCSControlUnit5Bits.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRam16x8.o build/objects/DCSRegister1Bit.o build/objects/DCSRegister4Bits.o build/objects/DCSRegister8Bits.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSPLD8In16Out.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/prj-FastControlUnit.o: .//src/Projects/prj-FastControlUnit.cpp .//src/Projects/prj-FastControlUnit.hpp build/objects/DCSPLD8In16Out.o build/objects/DCSDisplayNBits.o build/objects/DCSEngine.o build/objects/DCSLog.o build/objects/DCSRam256x16.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/prj-NoCUComputer.o: .//src/Projects/prj-NoCUComputer.cpp .//src/Projects/prj-NoCUComputer.hpp build/objects/DCSALU.o build/objects/DCSAnd.o build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSNode.o build/objects/DCSNot.o build/objects/DCSOutput.o build/objects/DCSRam16x8.o build/objects/DCSRegister4Bits.o build/objects/DCSRegister8Bits.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSTimer.o build/objects/DCSLog.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSClockSignal.o: .//src/Signals/DCSClockSignal.cpp .//include/DCSArbitrarySignal.hpp .//include/DCSClockSignal.hpp .//include/DCSEngine.hpp build/objects/DCSArbitrarySignal.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSArbitrarySignal.o: .//src/Signals/DCSArbitrarySignal.cpp .//include/DCSArbitrarySignal.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDisplayNBits.o: .//src/Displays/DCSDisplayNBits.cpp .//include/DCSDisplayNBits.hpp .//include/DCSEngine.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Register1BitWithEnable.o: .//src/Tests/test-Register1BitWithEnable.cpp .//src/Tests/test-Register1BitWithEnable.hpp build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRegister1BitWithEnable.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-BitStreamSignal.o: .//src/Tests/test-BitStreamSignal.cpp .//src/Tests/test-BitStreamSignal.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-FullAdder.o: .//src/Tests/test-FullAdder.cpp .//src/Tests/test-FullAdder.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSFullAdder.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-ControlUnit.o: .//src/Tests/test-ControlUnit.cpp .//src/Tests/test-ControlUnit.hpp build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRam256x16.o build/objects/DCSControlUnit4Bits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-TriStateBuffer.o: .//src/Tests/test-TriStateBuffer.cpp .//src/Tests/test-TriStateBuffer.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSTriStateBuffer.o build/objects/DCSNode.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-ALU.o: .//src/Tests/test-ALU.cpp .//src/Tests/test-ALU.hpp build/objects/DCSALU.o build/objects/DCSLog.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSDisplayNBits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-DLatch.o: .//src/Tests/test-DLatch.cpp .//src/Tests/test-DLatch.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSDLatch.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Ram.o: .//src/Tests/test-Ram.cpp .//src/Tests/test-Ram.hpp build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRam16x8.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-DLatchAsyncSR.o: .//src/Tests/test-DLatchAsyncSR.cpp .//src/Tests/test-DLatchAsyncSR.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSDLatchAsyncSR.o build/objects/DCSEngine.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Divider.o: .//src/Tests/test-Divider.cpp .//src/Tests/test-Divider.hpp build/objects/DCSClockDivider.o build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Register8Bits.o: .//src/Tests/test-Register8Bits.cpp .//src/Tests/test-Register8Bits.hpp build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRegister8Bits.o build/objects/DCSDisplayNBits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Nand3.o: .//src/Tests/test-Nand3.cpp .//src/Tests/test-Nand3.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o build/objects/DCSNand3.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-UnitDelay.o: .//src/Tests/test-UnitDelay.cpp .//src/Tests/test-UnitDelay.hpp build/objects/DCSLog.o build/objects/DCSEngine.o build/objects/DCSUnitDelay.o build/objects/DCSNot.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Register8BitsWithEnable.o: .//src/Tests/test-Register8BitsWithEnable.cpp .//src/Tests/test-Register8BitsWithEnable.hpp build/objects/DCSDisplayNBits.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRegister8BitsWithEnable.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-NotLoop.o: .//src/Tests/test-NotLoop.cpp .//src/Tests/test-NotLoop.hpp build/objects/DCSLog.o build/objects/DCSEngine.o build/objects/DCSNot.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-DFlipFlop.o: .//src/Tests/test-DFlipFlop.cpp .//src/Tests/test-DFlipFlop.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSDFlipFlop.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-And6.o: .//src/Tests/test-And6.cpp .//src/Tests/test-And6.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o build/objects/DCSAnd6.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Ram256x16.o: .//src/Tests/test-Ram256x16.cpp .//src/Tests/test-Ram256x16.hpp build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRam256x16.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-AddressDecoder32Bits.o: .//src/Tests/test-AddressDecoder32Bits.cpp .//src/Tests/test-AddressDecoder32Bits.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o build/objects/DCSAddressDecoder8Bits.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-AddressDecoder.o: .//src/Tests/test-AddressDecoder.cpp .//src/Tests/test-AddressDecoder.hpp build/objects/DCSAddressDecoder4Bits.o build/objects/DCSEngine.o build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSComponentArray.o build/objects/DCSDisplayNBits.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-MemoryProgrammer.o: .//src/Tests/test-MemoryProgrammer.cpp .//src/Tests/test-MemoryProgrammer.hpp build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRam16x8.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-SRLatch.o: .//src/Tests/test-SRLatch.cpp .//src/Tests/test-SRLatch.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSSRLatch.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-AndArray.o: .//src/Tests/test-AndArray.cpp .//src/Tests/test-AndArray.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSEngine.o build/objects/DCSAnd.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Nor3.o: .//src/Tests/test-Nor3.cpp .//src/Tests/test-Nor3.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o build/objects/DCSNor3.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Register16BitsWithEnable.o: .//src/Tests/test-Register16BitsWithEnable.cpp .//src/Tests/test-Register16BitsWithEnable.hpp build/objects/DCSDisplayNBits.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSRegister16BitsWithEnable.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Mux2To1.o: .//src/Tests/test-Mux2To1.cpp .//src/Tests/test-Mux2To1.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSMux2to1.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-UpCounter4Bits.o: .//src/Tests/test-UpCounter4Bits.cpp .//src/Tests/test-UpCounter4Bits.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-UpCounter.o: .//src/Tests/test-UpCounter.cpp .//src/Tests/test-UpCounter.hpp build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSOutput.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-all.o: .//src/Tests/test-all.cpp .//include/DCSLog.hpp .//include/DCSTimer.hpp .//src/Tests/test-ALU.hpp .//src/Tests/test-AddressDecoder.hpp .//src/Tests/test-AddressDecoder32Bits.hpp .//src/Tests/test-And6.hpp .//src/Tests/test-AndArray.hpp .//src/Tests/test-BitStreamSignal.hpp .//src/Tests/test-ControlUnit.hpp .//src/Tests/test-DFlipFlop.hpp .//src/Tests/test-DLatch.hpp .//src/Tests/test-DLatchAsyncSR.hpp .//src/Tests/test-Display.hpp .//src/Tests/test-Divider.hpp .//src/Tests/test-FullAdder.hpp .//src/Tests/test-JKMasterSlave.hpp .//src/Tests/test-MemoryProgrammer.hpp .//src/Tests/test-Mux2To1.hpp .//src/Tests/test-Nand3.hpp .//src/Tests/test-Nor3.hpp .//src/Tests/test-NotLoop.hpp .//src/Tests/test-Or.hpp .//src/Tests/test-Ram.hpp .//src/Tests/test-Ram256x16.hpp .//src/Tests/test-Register16BitsWithEnable.hpp .//src/Tests/test-Register1Bit.hpp .//src/Tests/test-Register1BitWithEnable.hpp .//src/Tests/test-Register8Bits.hpp .//src/Tests/test-Register8BitsWithEnable.hpp .//src/Tests/test-RippleAdder.hpp .//src/Tests/test-RisingEdgeDetector.hpp .//src/Tests/test-SRLatch.hpp .//src/Tests/test-TriStateBuffer.hpp .//src/Tests/test-UnitDelay.hpp .//src/Tests/test-UpCounter.hpp .//src/Tests/test-UpCounter4Bits.hpp .//src/Tests/test-Xor.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Display.o: .//src/Tests/test-Display.cpp .//src/Tests/test-Display.hpp build/objects/DCSComponentArray.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Xor.o: .//src/Tests/test-Xor.cpp .//src/Tests/test-Xor.hpp build/objects/DCSComponentArray.o build/objects/DCSDisplayNBits.o build/objects/DCSEngine.o build/objects/DCSInput.o build/objects/DCSLog.o build/objects/DCSNode.o build/objects/DCSOutput.o build/objects/DCSXor.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Register1Bit.o: .//src/Tests/test-Register1Bit.cpp .//src/Tests/test-Register1Bit.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSRegister1Bit.o build/objects/DCSEngine.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-RippleAdder.o: .//src/Tests/test-RippleAdder.cpp .//src/Tests/test-RippleAdder.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSRippleAdder8Bits.o build/objects/DCSEngine.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-Or.o: .//src/Tests/test-Or.cpp .//src/Tests/test-Or.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o build/objects/DCSOr.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-RisingEdgeDetector.o: .//src/Tests/test-RisingEdgeDetector.cpp .//src/Tests/test-RisingEdgeDetector.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSEngine.o build/objects/DCSUnitDelay.o build/objects/DCSNot.o build/objects/DCSAnd.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/test-JKMasterSlave.o: .//src/Tests/test-JKMasterSlave.cpp .//src/Tests/test-JKMasterSlave.hpp build/objects/DCSLog.o build/objects/DCSInput.o build/objects/DCSOutput.o build/objects/DCSJKLatchMasterSlaveAsyncSR.o build/objects/DCSEngine.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSComponent.o: .//src/Basic/DCSComponent.cpp .//include/DCSComponent.hpp .//include/DCSEngine.hpp .//include/DCSWire.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSComponentArray.o: .//src/Basic/DCSComponentArray.cpp .//include/DCSComponentArray.hpp .//include/DCSAnd.hpp .//include/DCSAnd3.hpp .//include/DCSAnd4.hpp .//include/DCSAnd6.hpp .//include/DCSAnd8.hpp .//include/DCSClockDivider.hpp .//include/DCSDFlipFlop.hpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSDLatch.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSFullAdder.hpp .//include/DCSInput.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSNand.hpp .//include/DCSNand3.hpp .//include/DCSNode.hpp .//include/DCSNor.hpp .//include/DCSNor3.hpp .//include/DCSNot.hpp .//include/DCSOr.hpp .//include/DCSOutput.hpp .//include/DCSRegister16BitsWithEnable.hpp .//include/DCSRegister1Bit.hpp .//include/DCSRegister1BitWithEnable.hpp .//include/DCSRegister8Bits.hpp .//include/DCSRegister8BitsWithEnable.hpp .//include/DCSSRLatch.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSUnitDelay.hpp .//include/DCSXor.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNode.o: .//src/Connections/DCSNode.cpp .//include/DCSNode.hpp .//include/DCSWire.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSWire.o: .//src/Connections/DCSWire.cpp .//include/DCSWire.hpp .//include/DCSLog.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSTriStateBuffer.o: .//src/Connections/DCSTriStateBuffer.cpp .//include/DCSTriStateBuffer.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSOutput.o: .//src/Connections/DCSOutput.cpp .//include/DCSOutput.hpp build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSInput.o: .//src/Connections/DCSInput.cpp .//include/DCSInput.hpp .//include/DCSClockSignal.hpp .//include/DCSEngine.hpp build/objects/DCSArbitrarySignal.o build/objects/DCSComponent.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSTriStateBuffer8Bits.o: .//src/Connections/DCSTriStateBuffer8Bits.cpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSLog.hpp build/objects/DCSComponentArray.o build/objects/DCSNode.o build/objects/DCSTriStateBuffer.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSPLD8In16Out.o: .//src/Decoders/DCSPLD8In16Out.cpp .//include/DCSPLD8In16Out.hpp .//include/DCSLog.hpp build/objects/DCSAddressDecoder8Bits.o build/objects/DCSComponent.o build/objects/DCSComponentArray.o build/objects/DCSInput.o build/objects/DCSOr.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAddressDecoder8Bits.o: .//src/Decoders/DCSAddressDecoder8Bits.cpp .//include/DCSAddressDecoder8Bits.hpp .//include/DCSAnd8.hpp .//include/DCSLog.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAddressDecoder4Bits.o: .//src/Decoders/DCSAddressDecoder4Bits.cpp .//include/DCSAddressDecoder4Bits.hpp .//include/DCSAnd4.hpp .//include/DCSLog.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSALU.o: .//src/Arithmetic/DCSALU.cpp .//include/DCSALU.hpp .//include/DCSLog.hpp build/objects/DCSRippleAdder8Bits.o build/objects/DCSComponent.o build/objects/DCSXor.o build/objects/DCSXor.o build/objects/DCSNor3.o build/objects/DCSAnd3.o build/objects/DCSNot.o build/objects/DCSComponentArray.o build/objects/DCSNode.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRippleAdder8Bits.o: .//src/Arithmetic/DCSRippleAdder8Bits.cpp .//include/DCSRippleAdder8Bits.hpp .//include/DCSFullAdder.hpp .//include/DCSLog.hpp build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSFullAdder.o: .//src/Arithmetic/DCSFullAdder.cpp .//include/DCSFullAdder.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSNode.o build/objects/DCSOr.o build/objects/DCSXor.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSClockDivider.o: .//src/Counters/DCSClockDivider.cpp .//include/DCSClockDivider.hpp .//include/DCSLog.hpp build/objects/DCSComponent.o build/objects/DCSJKLatchMasterSlaveAsyncSR.o build/objects/DCSNode.o build/objects/DCSOr.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSUpCounterWithLoadAndAsyncSR.o: .//src/Counters/DCSUpCounterWithLoadAndAsyncSR.cpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSLog.hpp build/objects/DCSClockDivider.o build/objects/DCSComponentArray.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDFlipFlopAsyncSR.o: .//src/Latches-async-SR/DCSDFlipFlopAsyncSR.cpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSDLatchAsyncSR.o build/objects/DCSNot.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDLatchAsyncSR.o: .//src/Latches-async-SR/DCSDLatchAsyncSR.cpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSNode.o build/objects/DCSNor3.o build/objects/DCSNot.o build/objects/DCSUnitDelay.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSJKLatchMasterSlaveAsyncSR.o: .//src/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.cpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSLog.hpp build/objects/DCSAnd.o build/objects/DCSAnd3.o build/objects/DCSNode.o build/objects/DCSNor3.o build/objects/DCSNot.o 
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -rf build

cleanall:
	rm -rf build gui/performance-analyzer/assets/* gui/logic-analyzer/assets/*