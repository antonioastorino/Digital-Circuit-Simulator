# Makefile auto generated using custom generator

CFLAGS=-c -Wextra -std=c++11 -O$(OPT) -g
CC=g++
INC= -I.//include\

.PHONY: all clean check-out-value make-opt check-opt-value

all: check-out-value

check-out-value:
	@[ -d "build/objects" ] || mkdir -p build/objects
	@[ -d "build" ] || mkdir -p build
	@if [ "$(OUT)" == "" ]; then\
		make check-opt-value OUT=out OPT=$(OPT) ;\
	else\
		make check-opt-value OUT=$(OUT) OPT=$(OPT) ;\
	fi

check-opt-value:
	[ "$(OPT)" == "" ] && make make-opt OUT=$(OUT) OPT=0 || make make-opt OUT=$(OUT) OPT=$(OPT)

make-opt:
	if [ ! -f "build/.$(OUT)-$(OPT)" ] || [ ! -f "build/$(OUT)-$(OPT)" ]; then \
		rm -rf build/objects/*; \
		mkdir -p build/objects; \
		touch build/.$(OUT)-$(OPT); \
	fi
	make build/$(OUT)-$(OPT) OUT=$(OUT) OPT=$(OPT);

build/$(OUT)-$(OPT): build/objects/DCSEngine.o build/objects/DCSNand3.o build/objects/DCSNor.o build/objects/DCSNot.o build/objects/DCSUnitDelay.o build/objects/DCSNand.o build/objects/DCSAnd6.o build/objects/DCSAnd.o build/objects/DCSOr.o build/objects/DCSAnd4.o build/objects/DCSNor3.o build/objects/DCSAnd3.o build/objects/DCSXor.o build/objects/DCSMux2to1.o build/objects/DCSRegister1Bit.o build/objects/DCSRam16x8.o build/objects/DCSRegister8Bits.o build/objects/DCSSRLatch.o build/objects/DCSDFlipFlop.o build/objects/DCSDLatch.o build/objects/DCSClockSignal.o build/objects/DCSArbitrarySignal.o build/objects/DCSDisplayNBits.o build/objects/DCSLog.o build/objects/Register8Bits-Test.o build/objects/UpCounter-Test.o build/objects/Display-Test.o build/objects/RamProgrammer-Test.o build/objects/FirstProgram-Test.o build/objects/Nor3-Test.o build/objects/DLatch-Test.o build/objects/TriStateBuffer-Test.o build/objects/BitStreamSignal-Test.o build/objects/CountAndStore-Test.o build/objects/Divider-Test.o build/objects/RippleAdder-Test.o build/objects/Nand3-Test.o build/objects/NotLoop-Test.o build/objects/Or-Test.o build/objects/DFlipFlop-Test.o build/objects/UnitDelay-Test.o build/objects/Mux2To1-Test.o build/objects/SRLatch-Test.o build/objects/JKMasterSlave-Test.o build/objects/AndArray-Test.o build/objects/Ram-Test.o build/objects/RisingEdgeDetector-Test.o build/objects/FullAdder-Test.o build/objects/DLatchAsyncSR-Test.o build/objects/And6-Test.o build/objects/Register1Bit-Test.o build/objects/DCSComponent.o build/objects/DCSComponentArray.o build/objects/DCSMemoryProgrammer.o build/objects/DCSNode.o build/objects/DCSWire.o build/objects/DCSTriStateBuffer.o build/objects/DCSOutput.o build/objects/DCSInput.o build/objects/DCSTriStateBuffer8Bits.o build/objects/DCSAddressDecoder4Bits.o build/objects/DCSRippleAdder8Bits.o build/objects/DCSFullAdder.o build/objects/DCSClockDivider.o build/objects/DCSUpCounterWithLoadAndAsyncSR.o build/objects/main.o build/objects/DCSDFlipFlopAsyncSR.o build/objects/DCSDLatchAsyncSR.o build/objects/DCSJKLatchMasterSlaveAsyncSR.o
	$(CC) $(INC) -o $@ $^

build/objects/DCSEngine.o: .//src/DCSEngine.cpp .//include/DCSArbitrarySignal.hpp .//include/DCSInput.hpp .//include/DCSWire.hpp .//include/DCSEngine.hpp .//include/DCSLog.hpp .//include/DCSDisplayNBits.hpp .//include/DCSLog.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNand3.o: .//src/Gates/DCSNand3.cpp .//include/DCSNand3.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNor.o: .//src/Gates/DCSNor.cpp .//include/DCSNor.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNot.o: .//src/Gates/DCSNot.cpp .//include/DCSNot.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSUnitDelay.o: .//src/Gates/DCSUnitDelay.cpp .//include/DCSUnitDelay.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNand.o: .//src/Gates/DCSNand.cpp .//include/DCSNand.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd6.o: .//src/Gates/DCSAnd6.cpp .//include/DCSAnd6.hpp .//include/DCSAnd.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd.o: .//src/Gates/DCSAnd.cpp .//include/DCSAnd.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSOr.o: .//src/Gates/DCSOr.cpp .//include/DCSOr.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd4.o: .//src/Gates/DCSAnd4.cpp .//include/DCSAnd4.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNor3.o: .//src/Gates/DCSNor3.cpp .//include/DCSNor3.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAnd3.o: .//src/Gates/DCSAnd3.cpp .//include/DCSAnd3.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSXor.o: .//src/Gates/DCSXor.cpp .//include/DCSXor.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSMux2to1.o: .//src/Muxes-Demuxes/DCSMux2to1.cpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSMux2to1.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSOr.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister1Bit.o: .//src/Memory/DCSRegister1Bit.cpp .//include/DCSRegister8Bits.hpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSOr.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRam16x8.o: .//src/Memory/DCSRam16x8.cpp .//include/DCSRegister8Bits.hpp .//include/DCSRam16x8.hpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp .//include/DCSAddressDecoder4Bits.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRegister8Bits.o: .//src/Memory/DCSRegister8Bits.cpp .//include/DCSRegister8Bits.hpp .//include/DCSRegister1Bit.hpp .//include/DCSLog.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSSRLatch.o: .//src/Latches/DCSSRLatch.cpp .//include/DCSSRLatch.hpp .//include/DCSNor.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDFlipFlop.o: .//src/Latches/DCSDFlipFlop.cpp .//include/DCSDFlipFlop.hpp .//include/DCSLog.hpp .//include/DCSDLatch.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDLatch.o: .//src/Latches/DCSDLatch.cpp .//include/DCSDLatch.hpp .//include/DCSNode.hpp .//include/DCSSRLatch.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSClockSignal.o: .//src/Signals/DCSClockSignal.cpp .//include/DCSArbitrarySignal.hpp .//include/DCSClockSignal.hpp .//include/DCSEngine.hpp .//include/DCSArbitrarySignal.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSArbitrarySignal.o: .//src/Signals/DCSArbitrarySignal.cpp .//include/DCSArbitrarySignal.hpp .//include/DCSEngine.hpp  
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDisplayNBits.o: .//src/Displays/DCSDisplayNBits.cpp .//include/DCSDisplayNBits.hpp .//include/DCSEngine.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSLog.o: .//src/DCSLog.cpp .//include/DCSLog.hpp  
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Register8Bits-Test.o: .//src/Tests/Register8Bits-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSRegister8Bits.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/UpCounter-Test.o: .//src/Tests/UpCounter-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Display-Test.o: .//src/Tests/Display-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/RamProgrammer-Test.o: .//src/Tests/RamProgrammer-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSRam16x8.hpp .//include/DCSMemoryProgrammer.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/FirstProgram-Test.o: .//src/Tests/FirstProgram-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSRam16x8.hpp .//include/DCSMemoryProgrammer.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Nor3-Test.o: .//src/Tests/Nor3-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSNor3.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DLatch-Test.o: .//src/Tests/DLatch-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSDLatch.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/TriStateBuffer-Test.o: .//src/Tests/TriStateBuffer-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSNode.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/BitStreamSignal-Test.o: .//src/Tests/BitStreamSignal-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/CountAndStore-Test.o: .//src/Tests/CountAndStore-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSRegister8Bits.hpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Divider-Test.o: .//src/Tests/Divider-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSClockDivider.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/RippleAdder-Test.o: .//src/Tests/RippleAdder-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSRippleAdder8Bits.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Nand3-Test.o: .//src/Tests/Nand3-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSNand3.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/NotLoop-Test.o: .//src/Tests/NotLoop-Test.cpp .//include/DCSLog.hpp .//include/DCSEngine.hpp .//include/DCSNot.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Or-Test.o: .//src/Tests/Or-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSOr.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DFlipFlop-Test.o: .//src/Tests/DFlipFlop-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSDFlipFlop.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/UnitDelay-Test.o: .//src/Tests/UnitDelay-Test.cpp .//include/DCSLog.hpp .//include/DCSEngine.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Mux2To1-Test.o: .//src/Tests/Mux2To1-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSMux2to1.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/SRLatch-Test.o: .//src/Tests/SRLatch-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSSRLatch.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/JKMasterSlave-Test.o: .//src/Tests/JKMasterSlave-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/AndArray-Test.o: .//src/Tests/AndArray-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSEngine.hpp .//include/DCSAnd.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Ram-Test.o: .//src/Tests/Ram-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSRam16x8.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/RisingEdgeDetector-Test.o: .//src/Tests/RisingEdgeDetector-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/FullAdder-Test.o: .//src/Tests/FullAdder-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSFullAdder.hpp .//include/DCSEngine.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DLatchAsyncSR-Test.o: .//src/Tests/DLatchAsyncSR-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/And6-Test.o: .//src/Tests/And6-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSEngine.hpp .//include/DCSAnd6.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/Register1Bit-Test.o: .//src/Tests/Register1Bit-Test.cpp .//include/DCSLog.hpp .//include/DCSInput.hpp .//include/DCSOutput.hpp .//include/DCSRegister1Bit.hpp .//include/DCSEngine.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSComponent.o: .//src/Basic/DCSComponent.cpp .//include/DCSComponent.hpp .//include/DCSEngine.hpp .//include/DCSWire.hpp   
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSComponentArray.o: .//src/Basic/DCSComponentArray.cpp .//include/DCSComponentArray.hpp .//include/DCSAnd.hpp .//include/DCSAnd3.hpp .//include/DCSAnd4.hpp .//include/DCSAnd6.hpp .//include/DCSClockDivider.hpp .//include/DCSDFlipFlop.hpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSDLatch.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSFullAdder.hpp .//include/DCSInput.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSNand.hpp .//include/DCSNand3.hpp .//include/DCSNode.hpp .//include/DCSNor.hpp .//include/DCSNor3.hpp .//include/DCSNot.hpp .//include/DCSOr.hpp .//include/DCSOutput.hpp .//include/DCSRegister1Bit.hpp .//include/DCSRegister8Bits.hpp .//include/DCSSRLatch.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSUnitDelay.hpp .//include/DCSXor.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSMemoryProgrammer.o: .//src/Utilities/DCSMemoryProgrammer.cpp .//include/DCSMemoryProgrammer.hpp .//include/DCSEngine.hpp .//include/DCSLog.hpp .//include/DCSRam16x8.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSNode.o: .//src/Connections/DCSNode.cpp .//include/DCSWire.hpp .//include/DCSNode.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSWire.o: .//src/Connections/DCSWire.cpp .//include/DCSWire.hpp .//include/DCSLog.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSTriStateBuffer.o: .//src/Connections/DCSTriStateBuffer.cpp .//include/DCSTriStateBuffer.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSOutput.o: .//src/Connections/DCSOutput.cpp .//include/DCSOutput.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSInput.o: .//src/Connections/DCSInput.cpp .//include/DCSInput.hpp .//include/DCSClockSignal.hpp .//include/DCSEngine.hpp .//include/DCSArbitrarySignal.hpp .//include/DCSComponent.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSTriStateBuffer8Bits.o: .//src/Connections/DCSTriStateBuffer8Bits.cpp .//include/DCSTriStateBuffer8Bits.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSTriStateBuffer.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSAddressDecoder4Bits.o: .//src/Decoders/DCSAddressDecoder4Bits.cpp .//include/DCSAddressDecoder4Bits.hpp .//include/DCSAnd4.hpp .//include/DCSLog.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSRippleAdder8Bits.o: .//src/Arithmetic/DCSRippleAdder8Bits.cpp .//include/DCSRippleAdder8Bits.hpp .//include/DCSFullAdder.hpp .//include/DCSLog.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSFullAdder.o: .//src/Arithmetic/DCSFullAdder.cpp .//include/DCSFullAdder.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSXor.hpp .//include/DCSOr.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSClockDivider.o: .//src/Counters/DCSClockDivider.cpp .//include/DCSLog.hpp .//include/DCSClockDivider.hpp .//include/DCSComponent.hpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSNode.hpp .//include/DCSOr.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSUpCounterWithLoadAndAsyncSR.o: .//src/Counters/DCSUpCounterWithLoadAndAsyncSR.cpp .//include/DCSUpCounterWithLoadAndAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSClockDivider.hpp .//include/DCSComponentArray.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/main.o: .//src/main.cpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDFlipFlopAsyncSR.o: .//src/Latches-async-SR/DCSDFlipFlopAsyncSR.cpp .//include/DCSDFlipFlopAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSAnd.hpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSNot.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSDLatchAsyncSR.o: .//src/Latches-async-SR/DCSDLatchAsyncSR.cpp .//include/DCSDLatchAsyncSR.hpp .//include/DCSNode.hpp .//include/DCSNor3.hpp .//include/DCSUnitDelay.hpp .//include/DCSNot.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

build/objects/DCSJKLatchMasterSlaveAsyncSR.o: .//src/Latches-async-SR/DCSJKLatchMasterSlaveAsyncSR.cpp .//include/DCSJKLatchMasterSlaveAsyncSR.hpp .//include/DCSLog.hpp .//include/DCSNode.hpp .//include/DCSNor3.hpp .//include/DCSNot.hpp .//include/DCSAnd3.hpp .//include/DCSAnd.hpp 
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -rf build/objects