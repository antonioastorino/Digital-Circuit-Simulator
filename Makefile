#Makefile auto generated
CFLAGS=-c -Wall -std=c++11
CC=g++
INC= -I.//include\

all: DCS.out

DCS.out: build/DCSEngine.o build/DCSNand3.o build/DCSNor.o build/DCSNot.o build/DCSUnitDelay.o build/DCSNand.o build/DCSAnd6.o build/DCSAnd.o build/DCSOr.o build/DCSAnd4.o build/DCSNor3.o build/DCSAnd3.o build/DCSXor.o build/DCSMux2to1.o build/DCSRegister1Bit.o build/DCSRam16x8.o build/DCSRegister8Bits.o build/DCSSRLatch.o build/DCSDFlipFlop.o build/DCSDLatch.o build/DCSClockSignal.o build/DCSArbitrarySignal.o build/DCSDisplayNBits.o build/DCSLog.o build/Register8Bits-Test.o build/UpCounter-Test.o build/Display-Test.o build/RamProgrammer-Test.o build/FirstProgram-Test.o build/Nor3-Test.o build/DLatch-Test.o build/TriStateBuffer-Test.o build/BitStreamSignal-Test.o build/CountAndStore-Test.o build/Divider-Test.o build/RippleAdder-Test.o build/Nand3-Test.o build/Or-Test.o build/DFlipFlop-Test.o build/NorLoop-Test.o build/UnitDelay-Test.o build/Mux2To1-Test.o build/SRLatch-Test.o build/JKMasterSlave-Test.o build/AndArray-Test.o build/Ram-Test.o build/RisingEdgeDetector-Test.o build/FullAdder-Test.o build/DLatchAsyncSR-Test.o build/And6-Test.o build/Register1Bit-Test.o build/DCSComponent.o build/DCSComponentArray.o build/DCSMemoryProgrammer.o build/DCSNode.o build/DCSWire.o build/DCSTriStateBuffer.o build/DCSOutput.o build/DCSInput.o build/DCSTriStateBuffer8Bits.o build/DCSAddressDecoder4Bits.o build/DCSRippleAdder8Bits.o build/DCSFullAdder.o build/DCSClockDiv2WithEnableAndLoad.o build/DCSUpCounterWithLoadAndAsyncSR.o build/main.o build/DCSDFlipFlopAsyncSR.o build/DCSDLatchAsyncSR.o build/DCSJKLatchMasterSlaveAsyncSR.o
	$(CC) $(INC) -o $@ build/DCSEngine.o build/DCSNand3.o build/DCSNor.o build/DCSNot.o build/DCSUnitDelay.o build/DCSNand.o build/DCSAnd6.o build/DCSAnd.o build/DCSOr.o build/DCSAnd4.o build/DCSNor3.o build/DCSAnd3.o build/DCSXor.o build/DCSMux2to1.o build/DCSRegister1Bit.o build/DCSRam16x8.o build/DCSRegister8Bits.o build/DCSSRLatch.o build/DCSDFlipFlop.o build/DCSDLatch.o build/DCSClockSignal.o build/DCSArbitrarySignal.o build/DCSDisplayNBits.o build/DCSLog.o build/Register8Bits-Test.o build/UpCounter-Test.o build/Display-Test.o build/RamProgrammer-Test.o build/FirstProgram-Test.o build/Nor3-Test.o build/DLatch-Test.o build/TriStateBuffer-Test.o build/BitStreamSignal-Test.o build/CountAndStore-Test.o build/Divider-Test.o build/RippleAdder-Test.o build/Nand3-Test.o build/Or-Test.o build/DFlipFlop-Test.o build/NorLoop-Test.o build/UnitDelay-Test.o build/Mux2To1-Test.o build/SRLatch-Test.o build/JKMasterSlave-Test.o build/AndArray-Test.o build/Ram-Test.o build/RisingEdgeDetector-Test.o build/FullAdder-Test.o build/DLatchAsyncSR-Test.o build/And6-Test.o build/Register1Bit-Test.o build/DCSComponent.o build/DCSComponentArray.o build/DCSMemoryProgrammer.o build/DCSNode.o build/DCSWire.o build/DCSTriStateBuffer.o build/DCSOutput.o build/DCSInput.o build/DCSTriStateBuffer8Bits.o build/DCSAddressDecoder4Bits.o build/DCSRippleAdder8Bits.o build/DCSFullAdder.o build/DCSClockDiv2WithEnableAndLoad.o build/DCSUpCounterWithLoadAndAsyncSR.o build/main.o build/DCSDFlipFlopAsyncSR.o build/DCSDLatchAsyncSR.o build/DCSJKLatchMasterSlaveAsyncSR.o

build/DCSEngine.o: .//src/DCSEngine.cpp .//include/DCSEngine.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNand3.o: .//src/Gates/DCSNand3.cpp .//include/DCSNand3.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNor.o: .//src/Gates/DCSNor.cpp .//include/DCSNor.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNot.o: .//src/Gates/DCSNot.cpp .//include/DCSNot.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSUnitDelay.o: .//src/Gates/DCSUnitDelay.cpp .//include/DCSUnitDelay.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNand.o: .//src/Gates/DCSNand.cpp .//include/DCSNand.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd6.o: .//src/Gates/DCSAnd6.cpp .//include/DCSAnd6.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd.o: .//src/Gates/DCSAnd.cpp .//include/DCSAnd.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSOr.o: .//src/Gates/DCSOr.cpp .//include/DCSOr.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd4.o: .//src/Gates/DCSAnd4.cpp .//include/DCSAnd4.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNor3.o: .//src/Gates/DCSNor3.cpp .//include/DCSNor3.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAnd3.o: .//src/Gates/DCSAnd3.cpp .//include/DCSAnd3.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSXor.o: .//src/Gates/DCSXor.cpp .//include/DCSXor.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSMux2to1.o: .//src/Muxes-Demuxes/DCSMux2to1.cpp .//include/DCSMux2to1.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRegister1Bit.o: .//src/Memory/DCSRegister1Bit.cpp .//include/DCSRegister1Bit.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRam16x8.o: .//src/Memory/DCSRam16x8.cpp .//include/DCSRam16x8.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRegister8Bits.o: .//src/Memory/DCSRegister8Bits.cpp .//include/DCSRegister8Bits.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSSRLatch.o: .//src/Latches/DCSSRLatch.cpp .//include/DCSSRLatch.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDFlipFlop.o: .//src/Latches/DCSDFlipFlop.cpp .//include/DCSDFlipFlop.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDLatch.o: .//src/Latches/DCSDLatch.cpp .//include/DCSDLatch.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSClockSignal.o: .//src/Signals/DCSClockSignal.cpp .//include/DCSClockSignal.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSArbitrarySignal.o: .//src/Signals/DCSArbitrarySignal.cpp .//include/DCSArbitrarySignal.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDisplayNBits.o: .//src/Displays/DCSDisplayNBits.cpp .//include/DCSDisplayNBits.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSLog.o: .//src/DCSLog.cpp .//include/DCSLog.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Register8Bits-Test.o: .//src/Tests/Register8Bits-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/UpCounter-Test.o: .//src/Tests/UpCounter-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Display-Test.o: .//src/Tests/Display-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/RamProgrammer-Test.o: .//src/Tests/RamProgrammer-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/FirstProgram-Test.o: .//src/Tests/FirstProgram-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Nor3-Test.o: .//src/Tests/Nor3-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DLatch-Test.o: .//src/Tests/DLatch-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/TriStateBuffer-Test.o: .//src/Tests/TriStateBuffer-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/BitStreamSignal-Test.o: .//src/Tests/BitStreamSignal-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/CountAndStore-Test.o: .//src/Tests/CountAndStore-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Divider-Test.o: .//src/Tests/Divider-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/RippleAdder-Test.o: .//src/Tests/RippleAdder-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Nand3-Test.o: .//src/Tests/Nand3-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Or-Test.o: .//src/Tests/Or-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DFlipFlop-Test.o: .//src/Tests/DFlipFlop-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/NorLoop-Test.o: .//src/Tests/NorLoop-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/UnitDelay-Test.o: .//src/Tests/UnitDelay-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Mux2To1-Test.o: .//src/Tests/Mux2To1-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/SRLatch-Test.o: .//src/Tests/SRLatch-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/JKMasterSlave-Test.o: .//src/Tests/JKMasterSlave-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/AndArray-Test.o: .//src/Tests/AndArray-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Ram-Test.o: .//src/Tests/Ram-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/RisingEdgeDetector-Test.o: .//src/Tests/RisingEdgeDetector-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/FullAdder-Test.o: .//src/Tests/FullAdder-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DLatchAsyncSR-Test.o: .//src/Tests/DLatchAsyncSR-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/And6-Test.o: .//src/Tests/And6-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/Register1Bit-Test.o: .//src/Tests/Register1Bit-Test.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSComponent.o: .//src/Basic/DCSComponent.cpp .//include/DCSComponent.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSComponentArray.o: .//src/Basic/DCSComponentArray.cpp .//include/DCSComponentArray.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSMemoryProgrammer.o: .//src/Utilities/DCSMemoryProgrammer.cpp .//include/DCSMemoryProgrammer.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSNode.o: .//src/Connections/DCSNode.cpp .//include/DCSNode.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSWire.o: .//src/Connections/DCSWire.cpp .//include/DCSWire.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSTriStateBuffer.o: .//src/Connections/DCSTriStateBuffer.cpp .//include/DCSTriStateBuffer.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSOutput.o: .//src/Connections/DCSOutput.cpp .//include/DCSOutput.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSInput.o: .//src/Connections/DCSInput.cpp .//include/DCSInput.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSTriStateBuffer8Bits.o: .//src/Connections/DCSTriStateBuffer8Bits.cpp .//include/DCSTriStateBuffer8Bits.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSAddressDecoder4Bits.o: .//src/Decoders/DCSAddressDecoder4Bits.cpp .//include/DCSAddressDecoder4Bits.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSRippleAdder8Bits.o: .//src/Arithmetic/DCSRippleAdder8Bits.cpp .//include/DCSRippleAdder8Bits.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSFullAdder.o: .//src/Arithmetic/DCSFullAdder.cpp .//include/DCSFullAdder.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSClockDiv2WithEnableAndLoad.o: .//src/Counters/DCSClockDiv2WithEnableAndLoad.cpp .//include/DCSClockDiv2WithEnableAndLoad.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSUpCounterWithLoadAndAsyncSR.o: .//src/Counters/DCSUpCounterWithLoadAndAsyncSR.cpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/main.o: .//src/main.cpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDFlipFlopAsyncSR.o: .//src/Latches-async-SR/DCSDFlipFlopAsyncSR.cpp .//include/DCSDFlipFlopAsyncSR.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSDLatchAsyncSR.o: .//src/Latches-async-SR/DCSDLatchAsyncSR.cpp .//include/DCSDLatchAsyncSR.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/DCSJKLatchMasterSlaveAsyncSR.o: .//src/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.cpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -f build/*