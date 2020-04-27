# DCS
Digital circuit simulator - from logic gates up

Inspired by the work of [Ben Eater](https://www.youtube.com/watch?v=HyznrdDSSGM&list=PLowKtXNTBypGqImE405J2565dvjafglHU) and not having the possibility to follow his work with hardware, I have decided to write a circuit simulator and build on top of it a processor. I am trying to take into account the time dependency of the system evolution. However, in real hardware, the state change of every component depends on many factors such as the technology in use, noise, imperfections, and so on. It would be out of the scope of this project trying to simulate all these factors. As a good compromise, I define the unit delay `tau` as the maximum delay that any of the elementary logic gates (and, or, not, nand, nor, etc.) can exhibit. Time diagrams and constraints are based on the value of `tau` which can be seen as a free parameter whose value cannot be established a priori. Time itself is therefore discretized in steps of length `tau`.

Examples of how to use the component library are in the main.cpp file.

If you have questions or want to contribute to this project feel free to contact me.

Antonio.

## How to build (Mac and Linux)
You are welcome to build the project the way you prefer. However, you can also use the tool provided here.
#### Generate a Makefile file
Run

```
makeMakefile.sh
```
This script must be run every time you add, move, or remove a .cpp or .hpp project file.
#### Compile

```
make [OPT=<x>] [OUT=<executable_file_name>]
```

`<x> = 0, 1, 2, or 3` is the optimization level. ```OPT``` not specified is equivalent to ```OPT=0```

`executable_file_name` is the name of the executable file, which will be placed in the `./build` folder and saved with the suffix `-<x>`. The default name is `out`.

The compiled object files will be located in `./build/objects`.

To erase the `./build` folder, run

```
make clean
```

#### Example:
```
make					# produces ./build/out-0
make OPT=2 OUT=test		# produces ./build/test-2 with optimization level 2
```
#### Known issue
```
make OUT=name OPT=0 # ok
make OUT=name OPT=1 # ok
make OUT=name OPT=0 # will override ./build/name-0 without recompiling the object files
```
##### Workaround: don't do that! (or run `make clean` first)
## Documentation automatically generated on Mon Apr 27 11:30:18 CEST 2020
NOTE: Generator under construction - be patient :)

```
 ## Class DCSDLatch
 Implements a D Latch
 Input 0 (data) needs to be ready at least 1 tau before input 1 (enable) is asserted.
 Input 1 and 0 must be stable at least 2 tau.
 The output is stable after 4 tau from the change in the input
 Here is an example:
       |  ___
 DATA: | X___XXXXXXXX
       |  ^ start
       |   __
 EN:   | __  ________
       |
       |     ________
 Q:    | XXXX________
       |      _______
 !Q:   | XXXXX_______
       |      ^ ready
```


```
 ## Class DCSAnd6
 Implements the AND gate with 3 inputs as an array of two DCSAnd3 AND'ed together by an AND gate
```


```
 ## Class DCSDisplayNBits


```


```
 ## Class DCSOr
 Implements the OR gate
```


```
 ## Class DCSAnd
 Implements the AND gate
```


```
 ## Class DCSAnd4
 Implements the AND gate with 4 inputs
```


```
 ## Class DCSInput
 This class is needed to provide controlled inputs to the circuit from the external world.
 In the initialization procedure, the Engine will start by propagating the values
 coming from this component first.
 Initialization 1
 DCSInput I0("I0");
 The signal can be attached afterwards using one of the following methods:
 - assign a constant value
 		void makeSignal(bool constValue);
 - assign a signal that changes at given time intervals, defined in 'transitions'
 		void makeSignal(transitions signal, bool initVal = 0, bool synch = false);
 		For example, a signal that starts at 0 and changes after 3 clock cycles and then
 again after 2 clock cycles can be obtained as follows:
 		@example makeSignal({2, 3}, 0, true);
 - assign a signal expressed as a string of bits
 		void makeSignal(std::string signal, bool synch = false);
 		To generate the same signal as in the previous example, you can use
 		@example makeSignal("001110");
 - assign a square wave
      void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
 Initialization 2
 DCSInput I0("I0", 1); // initialized with constant value 1
 @example Initialization 3
 DCSInput I0("I0", {2,2,3}, true); // initialized with a signal that will evolve with
 synchronously with the clock (synch = true) as follows: Start with value 0 and stay at 0 for 2
 clock cycles Switch to 1 and stay at 1 for 2 clock cycles Switch to 0 and stay at 0 for 3 clock
 cycles Switch to 1 and stay at 1 indefinitely. NOTE: if you want the signal to start with a 1,
 initialize with {0, ..., ...}
```


```
 ## Class DCSNor3
 Implements the NOR gate with 3 inputs
```


```
 ## Class DCSAnd3
 Implements the AND gate with 3 inputs
```


```
 ## Class DCSJKLatchMasterSlaveAsyncSR
 Implements the JK Latch Master Slave with asynchronous reset.
 IMPORTANT: the input value is read when the clock is low.
 Inputs 0 (J) and 1 (K) must be stable for at least 1 tau before and 1 tau after the clock rising
 edge.
 The output is read 4 tau after the rising edge of the clock. Inputs 3 (Clear) and 4 (Preset) must
 be stable at least 3 tau for the reset to have effect (after 3 tau) Here is an example:
```


```
 ## Class DCSDLatchAsyncSR
 Implements a D Latch with asynchronous Set and Reset
 Pinout:
 0 -> In Data
 1 -> In Enable
 2 -> In Asynchronous Reset (Clear)
 3 -> In Asynchronous Set (Preset)

 The time diagram is a merge of D-Latch and SR-Latch: when S and R are both low, this component
 behaves exactly like a D-Latch. When Enable is low, it behaves exactly like an SR-Latch. NOTE: do
 now use Enable when S or R are high.
```


```
 ## Class DCSRam16x8
 Implements a Ram module of 16 bytes.
 When inputs 13 to 16 (address) change, the output changes after 3 tau, independently of the
 clock. Since the Load signal of each individual register (here called Write - input 4) is AND'ed
 with the address decoder, compared to a single register, the RAM needs the address to be ready 3
 taus before the Load of each address.

 The write sequence is
       |  ___
 ADDR: | X___XXXXXXXX
       |  ^ start
       |   ____
 WRITE:| XX    XXXXXX
       |     ___
 DATA: | XXXX   XXXXX
       | ______  ____
 CLK:  |       __

 Input 0: Output enable
 Input 1: Clock
 Input 2: Clear
 Input 3: Preset
 Input 4: Write
 Input 5: Data in bit 0
 Input 6: Data in bit 1
 ...
 Input 12: Data in bit 7

 Input 13: Address bit 0
 Input 14: Address bit 1
 Input 15: Address bit 2
 Input 16: Address bit 3

 Out   0: Data out bit 0
 Out   1: Data out bit 1
 ...
```


```
 ## Class DCSComponentArray
 Generates an array of identical components.
```


```
 ## Class DCSClockDivider
 This clock divider (by 2) is mainly meant to be used as a building block for counters.
 The minimum clock period is 10 (5 high + 5 low) taus.

 Inputs 0 (Data) and 1 (Load) must be stable for at least 4 taus before and 1 tau after the clock
 rising edge. The resulting output is displayed 5 taus after the rising edge.
 Inputs 3 (Clear) and 4 (Preset) are directly connected to the internal JK master-slave. They must
 be stable for at least 3 taus and their effect is visible 3 taus after they are set.
 Input 5 (Count in) asserts both J and K in the internal latch with a delay of 2 taus. Therefore,
 it has to remain stable from 3 taus to 1 taus before the clock rising edge while Load is low.
 
 Output 2 (Count out) is high when input 5 and out 0 are high, with a delay of 1 tau. When
 connecting several dividers in cascade, this delay is multiplied by the number of dividers. This
 has to be taken into account when choosing the clock speed.
```


```
 ## Class DCSNand
 Implements the NAND gate
```


```
 ## Class DCSDFlipFlop_hpp
 
 Input 0 (data) needs to be ready not later than the time of input 1 (clock) assertion.
 Input 1 and 0 must be stable at least 2 tau.
 The output is stable after 4 tau from the change in the input
 Here is an example:
 	     |
 DATA: | X___XXXXXXXX
 	     |  ^ start
 	     |  __
 CLK:  | _  ________
 	     |
 	     |
 Q:    | XXXX________
       |      _______
 !Q:   | XXXXX
       |      ^ ready
```


```
 ## Class DCSOutput
 This component has no logical functions but is used to connect any floating output.
 Unconnected outputs generate errors!
 Also, by naming the used instance of this class, the connected input is probed and hence it can
 be displayed.
```


```
 ## Class DCSNor
 Implements the NOR gate
```


```
 ## Class DCSRegister1Bit
 Input 4 (load) must be asserted at least 3 tau before the clock falling edge.
 Input 0 (Data) must be stable at least 2 tau before the clock falling edge.
 Both have to be stable for at least 1 tau after the clock falling edge.
 Inputs 2 (clear) and 3 (preset) work the same as in the SR latch. Use them with input 4 low.
 Here is an example:
       |  ____
 LOAD: | X    XXXXXXXX
       |  ^ start
       |   ___
 DATA: | XX   XXXXXXXX
       | ____  _______
 CLK:  |     __
       |          ____
 Q:    | _________
       | ________
!Q:    |         _____
                  ^ ready

 PINOUT
 Input 0: Output Enable
 Input 1: Clock
 Input 2: Clear
 Input 3: Preset
 Input 4: Load
 Input 5: Data in
 Out   0: Data out
```


```
 ## Class DCSComponent
 Base virtual class for every logic component.
```


```
 ## Class DCSNot
 Implements the NOT gate
```


```
 ## Class DCSDFlipFlopAsyncSR
 D Flip-flop with asynchronous Set and Reset
```


```
 ## Class DCSEngine
 Static class providing 
```


```
 ## Class DCSClockSignal
 Generates a square wave with period 2 * `halfPeriod`
```


```
 ## Class DCSNand3
 Implements the NAND gate with 3 inputs
```


```
 ## Class DCSArbitrarySignal
 Generates a binary signal for use as input signal
 @param levelDurationVector	contains a vector of values corresponding to duration of each
 logical level.
 @param synch					selects the units for each logic level duration
 The units for the levels are:
 - tau            if synch = 0
 - clockPeriods   if synch = 1
```

