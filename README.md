# DCS
## Digital circuit simulator - from logic gates up

Inspired by the work of [Ben Eater](https://www.youtube.com/watch?v=HyznrdDSSGM&list=PLowKtXNTBypGqImE405J2565dvjafglHU) and not having the possibility to follow his work with hardware, I have decided to write a circuit simulator and build on top of it a processor. I am trying to take into account the time dependency of the system evolution. However, in real hardware, the state change of every component depends on many factors such as the technology in use, noise, imperfections, and so on. It would be out of the scope of this project trying to simulate all these factors. As a good compromise, I define the unit delay `tau` as the maximum delay that any of the elementary logic gates (and, or, not, nand, nor, etc.) can exhibit. Time diagrams and constraints are based on the value of `tau` which, can be seen as a free parameter whose value cannot be established a priori. Time itself is therefore discretized in steps of length `tau`.

Examples of how to use the component library are located in `./scr/Tests` folder.

## How to build (Mac and Linux)
You are welcome to build the project the way you prefer. However, you can also use the tool provided here.
### Generate a Makefile file
Run

```
bin/makeMakefile.sh
```
This script must be run every time you add, move, or remove a .cpp or .hpp project file.
### Build and run

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
There exist several ways to build. The simplest are as follows
```
make					# produces ./build/out-0
make OPT=2 OUT=test		# produces ./build/test-2 with optimization level 2
```
In addition, you can choose to build and run using

```
bin/build-run.sh [<TEST_NUMBER>]              # build and run <TEST_NUMBER>
bin/build-run-save.sh [<TEST_NUMBER>]         # build and run and save the output of <TEST_NUMBER>
bin/clean-build-run-save.sh [<TEST_NUMBER>]   # clean build, run, and save the output of <TEST_NUMBER>
```

If <TEST_NUMBER> (=0, 1, ... N) is specified, the corresponding test will be run righ after compilation. Chech `src/main.cpp` to see the list of tests available. If N is not specified, the default test is run.

The output is saved in `./gui/assets`. 

To specify the desired optimization level (by default equal to 0), the above instructions can be executed while <u>adding a second parameter between 0 and 3</u>. For instance

```
bin/build-run-save.sh 3 2

```
will build and run test number 3 with optimization level 2.
#### Known issue
```
make OUT=name OPT=0 # ok
make OUT=name OPT=1 # ok
make OUT=name OPT=0 # will override ./build/name-0 without recompiling the object files
```
##### Workaround: don't do that! (or run `make clean` first)

## How to display the data
A small web application can be found in the `./gui/` folder. At the time of writing, the interface looks as shown in the following figure
<!--[![web-gui-image](https://github.com/antonioastorino/DCS/blob/master/gui/images/web-app-0.png)]-->
![web-gui-image](images/web-gui-0.png)
To load one or more file, open the `./gui/assets/` folder and select one or more files from there. Those files are generated when running the script `build-run-save.sh` or `clean-build-run-save.sh`, located in the `./bin/` folder. If you don't have any, you can find some samples in `./gui/assets/samples/`.

The gui allows to

- select the desired file from the dropdown menu
- set the horizontal and vertical stretching factors
- scroll left-right by using the `Start` slider (swiping left right is disabled to avoid undesired page swiping)
- scroll up-down by using the regular mouse wheel or trackpad
- refresh the image without refreshing the page by clicking on `Refresh` - very useful if you re-build and want to see the updated result from the same file.
## Documentation automatically generated on Fri May  1 20:36:38 CEST 2020
NOTE: Generator under construction - be patient :)

## Class DCSDLatch

Implements a D Latch
Input 0 (data) needs to be ready at least 1 tau before input 1 (enable) is asserted.
Input 1 and 0 must be stable at least 2 tau.
The output is stable after 4 tau from the change in the input
#### Time diagram
```
|       |  ___
| DATA: | X___XXXXXXXX
|       |  ^ start
|       |   __
| EN:   | __  ________
|       |
|       |     ________
| Q:    | XXXX________
|       |      _______
| !Q:   | XXXXX_______
|       |      ^ ready
```



## Class DCSAnd6

Implements the AND gate with 3 inputs as an array of two DCSAnd3 AND'ed together by an AND gate


## Class DCSDisplayNBits





## Class DCSOr

Implements the OR gate


## Class DCSAnd

Implements the AND gate


## Class DCSAnd4

Implements the AND gate with 4 inputs


## Class DCSInput

This class is needed to provide controlled inputs to the circuit from the external world.
In the initialization procedure, the Engine will start by propagating the values
coming from this component first.
Initialization 1
DCSInput I0("I0");
The signal can be attached afterwards using one of the following methods:

- assign a constant value

```
void makeSignal(bool constValue);

```
- assign a signal that changes at given time intervals, defined in 'transitions'

```
void makeSignal(transitions signal, bool initVal = 0, bool synch = false);
```
For example, a signal that starts at 0 and changes after 3 clock cycles and then
again after 2 clock cycles can be obtained as follows:

```
makeSignal({2, 3}, 0, true);
```
- assign a signal expressed as a string of bits
void makeSignal(std::string signal, bool synch = false);
To generate the same signal as in the previous example, you can use
```makeSignal("001110");```
- assign a square wave
void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
Initialization 2
DCSInput I0("I0", 1); // initialized with constant value 1


## Class DCSNor3

Implements the NOR gate with 3 inputs


## Class DCSAnd3

Implements the AND gate with 3 inputs


## Class DCSJKLatchMasterSlaveAsyncSR

Implements the JK Latch Master Slave with asynchronous reset.
IMPORTANT: the input value is read when the clock is low.
Inputs 0 (J) and 1 (K) must be stable for at least 1 tau before and 1 tau after the clock rising
edge.
The output is read 4 tau after the rising edge of the clock. Inputs 3 (Clear) and 4 (Preset) must
be stable at least 3 tau for the reset to have effect (after 3 tau)

#### Time diagram
```
|      |   __
| J:   | XX  XXXXXXXX
|      |   ^ start
|      |   __
| K:   | XX  XXXXXXXX
|      |    __
| CLK: | X__  \\\  go down any time 2 tau after rising edge
|      |    ^ stored
|      |        _____
| Q:   | _______
|      | ______
|!Q:   |       ______
|      |        ^ ready
```



## Class DCSUpCounterWithLoadAndAsyncSR

This component is an up-counter with syncrhonous load and asynchronous clear and reset.
Internally, there are N clock dividers which share most of the control inputs,
hence converging to nodes.
Input 0 (Count in) of the counter is connected to the first divider only.
Inputs 1 to 4 are connected to the node array with indices 0 to 3, respectively.
The other N remaining inputs (Data 0 to N-1) are numbered from 5 to 5 + N.
Each of them is connected to input 0 (Data) of the corresponding divider.
The outputs from 0 to N-1 (Q) correspond to output 0 (array Q) of a divider.
Output N (array Count out) corresponds to output 2 (Count out) of the last divider.

#### Pinout
```
IN  0         - Count in (corresponding to input 5 in the internal divider)
IN  1         - Load  - node arrray with index 0
IN  2         - Clock - node arrray with index 1
IN  3         - Clear - node arrray with index 2
IN  4         - Preset - node arrray with index 3
IN  5         - Bit 0
IN  6         - Bit 1
IN  ...
IN  5 + N-1   - Bit N-1;
OUT 0         - Bit 0
OUT 1         - Bit 1
...
OUT N-1 - Bit N-1
OUT N - Count out
```

#### Table

| LD | C_IN | CLK | Function
|----|:-----|:----|:--------
|  0 |   0  |  X  |  Pause
|  0 |   1  |  X  |  Count
|  1 |   X  |  X  |  Load


Input 0 (Cout in) follows the rule of input 5 of the first divider. Therefore, it hast to be set
from 3 to 1 tau before the clock rising edge. However, every Count in in the subsequent dividers
is delayed by 1 tau. In addition, the output byte of the counter is ready 5 tau after the clock
rising edge. As a consequence, supposing that the expected output is all 1's, the last Count in
will be ready 5+N-1 tau after the clock rising edge and, as usual, has to be ready 3 tau before
the next clock rising edge. Therefore, the clock period has to be at least 5+N-1+3 = 7+N tau.


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


## Class DCSRam16x8

Implements a Ram module of 16 bytes.
When inputs 13 to 16 (address) change, the output changes after 3 tau, independently of the
clock. Since the Load signal of each individual register (here called Write - input 4) is AND'ed
with the address decoder, compared to a single register, the RAM needs the address to be ready 3
taus before the Load of each address.

#### Time diagram
```
|       |  ___
| ADDR: | X___XXXXXXXX
|       |  ^ start
|       |   ____
| WRITE:| XX    XXXXXX
|       |     ___
| DATA: | XXXX   XXXXX
|       | ______  ____
| CLK:  |       __
|       |         ^ start
```

#### Pinout
```
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



## Class DCSComponentArray

Generates an array of identical components.


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


## Class DCSNand

Implements the NAND gate


## Class DCSDFlipFlop


Input 0 (data) needs to be ready not later than the time of input 1 (clock) assertion.
Input 1 and 0 must be stable at least 2 tau.
The output is stable after 4 tau from the change in the input
#### Time diagram
```
|       |
| DATA: | X___XXXXXXXX
|       |  ^ start
|       |  __
| CLK:  | _  ________
|       |
|       |
| Q:    | XXXX________
|       |      _______
| !Q:   | XXXXX
|       |      ^ ready
```



## Class DCSOutput

This component has no logical functions but is used to connect any floating output.
Unconnected outputs generate errors!
Also, by naming the used instance of this class, the connected input is probed and hence it can
be displayed.


## Class DCSNor

Implements the NOR gate


## Class DCSRegister1Bit

Input 4 (load) must be asserted at least 3 tau before the clock falling edge.
Input 0 (Data) must be stable at least 2 tau before the clock falling edge.
Both have to be stable for at least 1 tau after the clock falling edge.
Inputs 2 (clear) and 3 (preset) work the same as in the SR latch. Use them with input 4 low.

#### Time diagram
```
|       |  ____
| LOAD: | X    XXXXXXXX
|       |  ^ start
|       |   ___
| DATA: | XX   XXXXXXXX
|       | ____  _______
| CLK:  |     __
|       |          ____
| Q:    | _________
|       | ________
|!Q:    |         _____
|                  ^ ready
```

PINOUT:
Input 0: Output Enable
Input 1: Clock
Input 2: Clear
Input 3: Preset
Input 4: Load
Input 5: Data in
Out   0: Data out


## Class DCSComponent

Base virtual class for every logic component which provides components with the necessary
functionalities, e.g:

- connect with other components using `DCSWire` objects
- update the output based on the current state (values read at the input)
- keep track of which pins are not connected
- keep track of which pins are not reached during the initialization process

#### How to connect two components
Supposing we have two components, `compA` and `compB`, and we want to connect the output of the
first to the second. If `compA.getNumOfOutPins()` returns the same value as
`compB.getNumOfInPins()`, say `N`, the easiest way to perform the connection is by using the method

```
void connect(DCSComponent* const to, const std::vector<std::string>& probeNames = {});
```
as follows

```
compA.connect(&compB);
```
or

```
compA.connect(&compB, {"<probe_name1>", "<probe_name2>", ..., "<probe_nameN>"});
```
NOTE: Specifying the lables entails the probes to be prompted at run time.

This will connect the output pins of `compA` to the corresponding (same pin number) input pins of
`compB`. If this is not the desired order or the pin numbers do not match it is possible to connect one pin at a time using

```
void connect(DCSComponent* const to, uint16_t outPinNum, uint16_t inPinNum, const std::string& probeName = "");
```

In addition, one can select a range of output pins to connect to a range of input pins using

```
void connect(DCSComponent* const to, DCSPinNumRange outPinNumRange, DCSPinNumRange inPinNumRange, const std::vector<std::string>& probeNames = {});
```


## Class DCSNot

Implements the NOT gate


## Class DCSDFlipFlopAsyncSR

D Flip-flop with asynchronous Set and Reset


## Class DCSEngine

Static class providing


## Class DCSClockSignal

Generates a square wave with period 2 * `halfPeriod`


## Class DCSNand3

Implements the NAND gate with 3 inputs


## Class DCSArbitrarySignal

Generates a binary signal for use as input signal
@param levelDurationVector	contains a vector of values corresponding to duration of each
logical level.
@param synch					selects the units for each logic level duration
The units for the levels are:
- tau            if synch = 0
- clockPeriods   if synch = 1


## Class DCSMemoryProgrammer


