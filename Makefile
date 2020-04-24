# Makefile auto generated using custom generator

CFLAGS=-c -Wall -std=c++11
CC=g++
INC= -I.//include\
 -I.//src/Arithmetic\

all: DCS.out

DCS.out: build/DCSEngine.o build/DCSNand3.o build/DCSNor.o build/DCSNot.o build/DCSUnitDelay.o build/DCSNand.o build/DCSAnd6.o build/DCSAnd.o build/DCSOr.o build/DCSAnd4.o build/DCSNor3.o build/DCSAnd3.o build/DCSXor.o build/DCSMux2to1.o build/DCSRegister1Bit.o build/DCSRam16x8.o build/DCSRegister8Bits.o build/DCSSRLatch.o build/DCSDFlipFlop.o build/DCSDLatch.o build/DCSClockSignal.o build/DCSArbitrarySignal.o build/DCSDisplayNBits.o build/DCSLog.o build/Register8Bits-Test.o build/UpCounter-Test.o build/Display-Test.o build/RamProgrammer-Test.o build/FirstProgram-Test.o build/Nor3-Test.o build/DLatch-Test.o build/TriStateBuffer-Test.o build/BitStreamSignal-Test.o build/CountAndStore-Test.o build/Divider-Test.o build/RippleAdder-Test.o build/Nand3-Test.o build/NotLoop-Test.o build/Or-Test.o build/DFlipFlop-Test.o build/UnitDelay-Test.o build/Mux2To1-Test.o build/SRLatch-Test.o build/JKMasterSlave-Test.o build/AndArray-Test.o build/Ram-Test.o build/RisingEdgeDetector-Test.o build/FullAdder-Test.o build/DLatchAsyncSR-Test.o build/And6-Test.o build/Register1Bit-Test.o build/DCSComponent.o build/DCSComponentArray.o build/DCSMemoryProgrammer.o build/DCSNode.o build/DCSWire.o build/DCSTriStateBuffer.o build/DCSOutput.o build/DCSInput.o build/DCSTriStateBuffer8Bits.o build/DCSAddressDecoder4Bits.o build/DCSRippleAdder8Bits.o build/DCSFullAdder.o build/DCSClockDiv2WithEnableAndLoad.o build/DCSUpCounterWithLoadAndAsyncSR.o build/main.o build/DCSDFlipFlopAsyncSR.o build/DCSDLatchAsyncSR.o build/DCSJKLatchMasterSlaveAsyncSR.o
	$(CC) $(INC) -o $@ build/DCSEngine.o build/DCSNand3.o build/DCSNor.o build/DCSNot.o build/DCSUnitDelay.o build/DCSNand.o build/DCSAnd6.o build/DCSAnd.o build/DCSOr.o build/DCSAnd4.o build/DCSNor3.o build/DCSAnd3.o build/DCSXor.o build/DCSMux2to1.o build/DCSRegister1Bit.o build/DCSRam16x8.o build/DCSRegister8Bits.o build/DCSSRLatch.o build/DCSDFlipFlop.o build/DCSDLatch.o build/DCSClockSignal.o build/DCSArbitrarySignal.o build/DCSDisplayNBits.o build/DCSLog.o build/Register8Bits-Test.o build/UpCounter-Test.o build/Display-Test.o build/RamProgrammer-Test.o build/FirstProgram-Test.o build/Nor3-Test.o build/DLatch-Test.o build/TriStateBuffer-Test.o build/BitStreamSignal-Test.o build/CountAndStore-Test.o build/Divider-Test.o build/RippleAdder-Test.o build/Nand3-Test.o build/NotLoop-Test.o build/Or-Test.o build/DFlipFlop-Test.o build/UnitDelay-Test.o build/Mux2To1-Test.o build/SRLatch-Test.o build/JKMasterSlave-Test.o build/AndArray-Test.o build/Ram-Test.o build/RisingEdgeDetector-Test.o build/FullAdder-Test.o build/DLatchAsyncSR-Test.o build/And6-Test.o build/Register1Bit-Test.o build/DCSComponent.o build/DCSComponentArray.o build/DCSMemoryProgrammer.o build/DCSNode.o build/DCSWire.o build/DCSTriStateBuffer.o build/DCSOutput.o build/DCSInput.o build/DCSTriStateBuffer8Bits.o build/DCSAddressDecoder4Bits.o build/DCSRippleAdder8Bits.o build/DCSFullAdder.o build/DCSClockDiv2WithEnableAndLoad.o build/DCSUpCounterWithLoadAndAsyncSR.o build/main.o build/DCSDFlipFlopAsyncSR.o build/DCSDLatchAsyncSR.o build/DCSJKLatchMasterSlaveAsyncSR.o

build/DCSEngine.o: .//src/DCSEngine.cpp .//include/DCSHeader.h .//include/DCSArbitrarySignal.hpp .//include/DCSInput.hpp .//include/DCSWire.hpp .//include/DCSEngine.hpp .//include/DCSDisplayNBits.hpp .//include/DCSLog.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNand3.o: .//src/Gates/DCSNand3.cpp .//include/DCSHeader.h .//include/DCSNand3.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNor.o: .//src/Gates/DCSNor.cpp .//include/DCSHeader.h .//include/DCSNor.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNot.o: .//src/Gates/DCSNot.cpp .//include/DCSHeader.h .//include/DCSNot.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSUnitDelay.o: .//src/Gates/DCSUnitDelay.cpp .//include/DCSHeader.h .//include/DCSUnitDelay.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNand.o: .//src/Gates/DCSNand.cpp .//include/DCSHeader.h .//include/DCSNand.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd6.o: .//src/Gates/DCSAnd6.cpp .//include/DCSHeader.h .//include/DCSAnd6.hpp .//include/DCSAnd.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd.o: .//src/Gates/DCSAnd.cpp .//include/DCSHeader.h .//include/DCSAnd.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSOr.o: .//src/Gates/DCSOr.cpp .//include/DCSHeader.h .//include/DCSOr.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd4.o: .//src/Gates/DCSAnd4.cpp .//include/DCSHeader.h .//include/DCSAnd4.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNor3.o: .//src/Gates/DCSNor3.cpp .//include/DCSHeader.h .//include/DCSNor3.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd3.o: .//src/Gates/DCSAnd3.cpp .//include/DCSHeader.h .//include/DCSAnd3.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSXor.o: .//src/Gates/DCSXor.cpp .//include/DCSHeader.h .//include/DCSXor.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSMux2to1.o: .//src/Muxes-Demuxes/DCSMux2to1.cpp .//include/DCSHeader.h .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSMux2to1.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSOr.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRegister1Bit.o: .//src/Memory/DCSRegister1Bit.cpp .//include/DCSHeader.h .//include/DCSRegister8Bits.hpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSOr.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRam16x8.o: .//src/Memory/DCSRam16x8.cpp .//include/DCSHeader.h .//include/DCSRegister8Bits.hpp .//include/DCSRam16x8.hpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp .//src/Arithmetic/DCSAddressDecoder4Bits.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRegister8Bits.o: .//src/Memory/DCSRegister8Bits.cpp .//include/DCSHeader.h .//include/DCSRegister8Bits.hpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSSRLatch.o: .//src/Latches/DCSSRLatch.cpp .//include/DCSHeader.h .//include/DCSSRLatch.hpp .//include/DCSNor.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDFlipFlop.o: .//src/Latches/DCSDFlipFlop.cpp .//include/DCSHeader.h .//include/DCSDFlipFlop.hpp .//include/DCSLog.hpp .//include/DCSDLatch.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDLatch.o: .//src/Latches/DCSDLatch.cpp .//include/DCSHeader.h .//include/DCSDLatch.hpp .//include/DCSNode.hpp .//include/DCSSRLatch.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSClockSignal.o: .//src/Signals/DCSClockSignal.cpp .//include/DCSHeader.h .//include/DCSArbitrarySignal.hpp .//include/DCSClockSignal.hpp .//include/DCSEngine.hpp .//include/DCSArbitrarySignal.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSArbitrarySignal.o: .//src/Signals/DCSArbitrarySignal.cpp .//include/DCSHeader.h .//include/DCSArbitrarySignal.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDisplayNBits.o: .//src/Displays/DCSDisplayNBits.cpp .//include/DCSHeader.h .//include/DCSDisplayNBits.hpp .//include/DCSEngine.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSLog.o: .//src/DCSLog.cpp .//include/DCSHeader.h .//include/DCSLog.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Register8Bits-Test.o: .//src/Tests/Register8Bits-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSRegister8Bits.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/UpCounter-Test.o: .//src/Tests/UpCounter-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Display-Test.o: .//src/Tests/Display-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/RamProgrammer-Test.o: .//src/Tests/RamProgrammer-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSRam16x8.hpp .//include/DCSMemoryProgrammer.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/FirstProgram-Test.o: .//src/Tests/FirstProgram-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSRam16x8.hpp .//include/DCSMemoryProgrammer.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Nor3-Test.o: .//src/Tests/Nor3-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSNor3.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DLatch-Test.o: .//src/Tests/DLatch-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSDLatch.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/TriStateBuffer-Test.o: .//src/Tests/TriStateBuffer-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSNode.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/BitStreamSignal-Test.o: .//src/Tests/BitStreamSignal-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/CountAndStore-Test.o: .//src/Tests/CountAndStore-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSRegister8Bits.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Divider-Test.o: .//src/Tests/Divider-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSClockDiv2WithEnableAndLoad.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/RippleAdder-Test.o: .//src/Tests/RippleAdder-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSRippleAdder8Bits.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Nand3-Test.o: .//src/Tests/Nand3-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSNand3.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/NotLoop-Test.o: .//src/Tests/NotLoop-Test.cpp .//include/DCSHeader.h .//include/DCSEngine.hpp .//include/DCSNot.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Or-Test.o: .//src/Tests/Or-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSOr.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DFlipFlop-Test.o: .//src/Tests/DFlipFlop-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSDFlipFlop.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/UnitDelay-Test.o: .//src/Tests/UnitDelay-Test.cpp .//include/DCSHeader.h .//include/DCSEngine.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Mux2To1-Test.o: .//src/Tests/Mux2To1-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSMux2to1.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/SRLatch-Test.o: .//src/Tests/SRLatch-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSSRLatch.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/JKMasterSlave-Test.o: .//src/Tests/JKMasterSlave-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/AndArray-Test.o: .//src/Tests/AndArray-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSEngine.hpp .//include/DCSAnd.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Ram-Test.o: .//src/Tests/Ram-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSRam16x8.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/RisingEdgeDetector-Test.o: .//src/Tests/RisingEdgeDetector-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/FullAdder-Test.o: .//src/Tests/FullAdder-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSFullAdder.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DLatchAsyncSR-Test.o: .//src/Tests/DLatchAsyncSR-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/And6-Test.o: .//src/Tests/And6-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSAnd6.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Register1Bit-Test.o: .//src/Tests/Register1Bit-Test.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSRegister1Bit.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSComponent.o: .//src/Basic/DCSComponent.cpp .//include/DCSHeader.h .//include/DCSWire.hpp .//include/DCSEngine.hpp .//include/DCSComponent.hpp   
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSComponentArray.o: .//src/Basic/DCSComponentArray.cpp .//include/DCSComponentArray.hpp .//include/DCSAnd.hpp .//include/DCSAnd3.hpp .//include/DCSAnd4.hpp .//include/DCSAnd6.hpp .//include/DCSClockDiv2WithEnableAndLoad.hpp .//include/DCSDFlipFlop.hpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSDLatch.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSFullAdder.hpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSNand.hpp .//include/DCSNand3.hpp .//include/DCSNode.hpp .//include/DCSNor.hpp .//include/DCSNor3.hpp .//include/DCSNot.hpp .//include/DCSOr.hpp .//include/DCSOutput.hpp .//include/DCSRegister1Bit.hpp .//include/DCSRegister8Bits.hpp .//include/DCSSRLatch.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSUnitDelay.hpp .//include/DCSXor.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSMemoryProgrammer.o: .//src/Utilities/DCSMemoryProgrammer.cpp .//include/DCSHeader.h .//include/DCSMemoryProgrammer.hpp .//include/DCSEngine.hpp .//include/DCSLog.hpp .//include/DCSRam16x8.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNode.o: .//src/Connections/DCSNode.cpp .//include/DCSHeader.h .//include/DCSWire.hpp .//include/DCSNode.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSWire.o: .//src/Connections/DCSWire.cpp .//include/DCSHeader.h .//include/DCSWire.hpp .//include/DCSLog.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSTriStateBuffer.o: .//src/Connections/DCSTriStateBuffer.cpp .//include/DCSHeader.h .//include/DCSTriStateBuffer.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSOutput.o: .//src/Connections/DCSOutput.cpp .//include/DCSHeader.h .//include/DCSOutput.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSInput.o: .//src/Connections/DCSInput.cpp .//include/DCSHeader.h .//include/DCSInput.hpp .//include/DCSClockSignal.hpp .//include/DCSEngine.hpp .//include/DCSArbitrarySignal.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSTriStateBuffer8Bits.o: .//src/Connections/DCSTriStateBuffer8Bits.cpp .//include/DCSHeader.h .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAddressDecoder4Bits.o: .//src/Decoders/DCSAddressDecoder4Bits.cpp .//include/DCSHeader.h .//src/Arithmetic/DCSAddressDecoder4Bits.hpp .//include/DCSAnd4.hpp .//include/DCSLog.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRippleAdder8Bits.o: .//src/Arithmetic/DCSRippleAdder8Bits.cpp .//include/DCSHeader.h .//include/DCSRippleAdder8Bits.hpp .//include/DCSFullAdder.hpp .//include/DCSLog.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSFullAdder.o: .//src/Arithmetic/DCSFullAdder.cpp .//include/DCSHeader.h .//include/DCSFullAdder.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSXor.hpp .//include/DCSOr.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSClockDiv2WithEnableAndLoad.o: .//src/Counters/DCSClockDiv2WithEnableAndLoad.cpp .//include/DCSHeader.h .//include/DCSClockDiv2WithEnableAndLoad.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSOr.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSUpCounterWithLoadAndAsyncSR.o: .//src/Counters/DCSUpCounterWithLoadAndAsyncSR.cpp .//include/DCSHeader.h .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSClockDiv2WithEnableAndLoad.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/main.o: .//src/main.cpp .//include/DCSHeader.h 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDFlipFlopAsyncSR.o: .//src/Latches-async-SR/DCSDFlipFlopAsyncSR.cpp .//include/DCSHeader.h .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDLatchAsyncSR.o: .//src/Latches-async-SR/DCSDLatchAsyncSR.cpp .//include/DCSHeader.h .//include/DCSDLatchAsyncSR.hpp .//include/DCSNode.hpp .//include/DCSNor3.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSJKLatchMasterSlaveAsyncSR.o: .//src/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.cpp .//include/DCSHeader.h .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSNor3.hpp .//include/DCSNot.hpp .//include/DCSAnd3.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -f build/*