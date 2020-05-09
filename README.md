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

`<executable_file_name>` is the name of the executable file, which will be placed in the `./build` folder and saved with the suffix `-<x>`. The default name is `out`.

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
```

If `<TEST_NUMBER>` (=0, 1, ... N) is specified, the corresponding test will be run righ after compilation. Chech `src/main.cpp` to see the list of tests available. If N is not specified, the default test is run.

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

![web-gui-image](https://github.com/antonioastorino/DCS/blob/master/doc/images/web-gui-0.png)

To load one or more file, open the `./gui/assets/` folder and select one or more files from there. Those files are generated when running the script `build-run-save.sh` or `clean-build-run-save.sh`, located in the `./bin/` folder. If you don't have any, you can find some samples in `./gui/assets/samples/`.

The gui allows to

- select the desired file from the dropdown menu
- set the horizontal and vertical stretching factors
- scroll left-right by using the `Start` slider (swiping left right is disabled to avoid undesired page swiping)
- scroll up-down by using the regular mouse wheel or trackpad
- refresh the image without refreshing the page by clicking on `Refresh` - very useful if you re-build and want to see the updated result from the same file.
## Documentation automatically generated on Sat May  9 12:47:53 CEST 2020
NOTE: Generator under construction - be patient :)

## Class DCSDLatch

D Latch

#### Pinout
```
In 0  - Data in
In 1  - Enable
Out 0 - Q
Out 1 - !Q
```


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


`Data in` needs to be ready at least `1 tau` before `Enable` is asserted.
`Data` and `Enable` must be stable for at least 2 tau.
The output is stable after 4 tau from the change in the input.


## Class DCSAnd6

AND gate with 3 inputs as an array of two DCSAnd3 AND'ed together by an AND gate


## Class DCSDisplayNBits





## Class DCSOr

OR gate


## Class DCSAnd

AND gate


## Class DCSAnd4

AND gate with 4 inputs


## Class DCSFullAdder

Full adder.

#### Pinout
```
In  0 - A
In  1 - B
In  2 - Carry in

Out 0 - Sum
Out 1 - Carry out
```



## Class DCSInput

This class is needed to provide controlled inputs to the circuit from the external world.
In the initialization procedure, the Engine will start by propagating the values
coming from this component first.
### Initialization for arbitrary signal

```
DCSInput(std::string name);
```

The signal can be attached afterwards using one of the following methods:

- assign a constant value

```
void makeSignal(bool constValue);

```
- assign a signal that changes at given time intervals, defined in 'signal'

```
void makeSignal(transitions signal, bool initVal = 0, bool synch = false);
```

- assign a signal expressed as a string of bits
void makeSignal(std::string signal, bool synch = false);
To generate the same signal as in the previous example, you can use

```makeSignal("001110");```

- assign a square wave

```
void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
```

For example, a signal that starts at 0 and changes after 3 clock cycles and then
again after 2 clock cycles can be obtained as follows:

```makeSignal({2, 3}, 0, true);```

### Initialization with constant signal

```
DCSInput(std::string name, bool initValue);
```



## Class DCSNor3

NOR gate with 3 inputs


## Class DCSAnd3

AND gate with 3 inputs


## Class DCSRegister8Bits

8-bit register made up of 8 1-bit registers sharing the same control signals

#### Pinout
```
In 0    - Data in 0
In 1    - Data in 1
In 2    - Data in 2
In 3    - Data in 3
In 4    - Data in 4
In 5    - Data in 5
In 6    - Data in 6
In 7    - Data in 7
In 8    - Clock
In 9    - Clear
In 10   - Preset
In 11   - Load

Out 0   - Data out 0
Out 1   - Data out 1
Out 2   - Data out 2
Out 3   - Data out 3
Out 4   - Data out 4
Out 5   - Data out 5
Out 6   - Data out 6
Out 7   - Data out 7
```



## Class DCSJKLatchMasterSlaveAsyncSR

J-K Latch Master-Slave with asynchronous reset.
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
In 0         - Count in (corresponding to input 5 in the internal divider)
In 1         - Load  - node arrray with index 0
In 2         - Clock - node arrray with index 1
In 3         - Clear - node arrray with index 2
In 4         - Preset - node arrray with index 3
In 5         - Bit 0
In 6         - Bit 1
...
In 5 + N-1   - Bit N-1;

Out 0         - Bit 0
Out 1         - Bit 1
...
Out N-1       - Bit N-1
Out N         - Count out
```


#### Table

| LD | C_IN | CLK | Function
|----|:-----|:----|:--------
|  0 |   0  |  X  |  Pause
|  0 |   1  |  X  |  Count
|  1 |   X  |  X  |  Load



`Cout in` follows the rule of input 5 of the first divider. Therefore, it hast to be set
from `3` to `1 tau` before the clock rising edge. However, every `Count in` in the subsequent dividers
is delayed by `1 tau`. In addition, the output byte of the counter is ready `5 tau` after the clock
rising edge. As a consequence, supposing that the expected output is all 1's, the last `Count in`
will be ready `5+N-1 tau` after the clock rising edge and has to be ready `3 tau` before
the next clock rising edge. Therefore, the clock period has to be at least `5+N-1+3 = 7+N tau`.


## Class DCSDLatchAsyncSR

D Latch with asynchronous Set and Reset

#### Pinout
```
In 0    - Data
In 1    - Enable
In 2    - Asynchronous Reset (Clear)
In 3    - Asynchronous Set (Preset)

Out 0   - Q
Out 1   - !Q
```


The time diagram is a merge of D-Latch and SR-Latch: when S and R are both low, this component
behaves exactly like a D-Latch. When Enable is low, it behaves exactly like an SR-Latch.

IMPORTANT: do not assert `Enable` when `S` or `R` are high.


## Class DCSRam16x8

Ram module of 16 bytes.

#### Pinout
```
In 0    - Data in 0
In 1    - Data in 1
In 2    - Data in 2
In 3    - Data in 3
In 4    - Data in 4
In 5    - Data in 5
In 6    - Data in 6
In 7    - Data in 7
In 8    - Address 0
In 9    - Address 1
In 10   - Address 2
In 11   - Address 3
In 12   - Clock
In 13   - Clear
In 14   - Preset
In 15   - Write
In 16   - Output enable

Out 0   - Data out 0
Out 1   - Data out 1
Out 2   - Data out 2
Out 3   - Data out 3
Out 4   - Data out 4
Out 5   - Data out 5
Out 6   - Data out 6
Out 7   - Data out 7
```


#### Time diagram
```
|       |  ___
| ADDR: | X___XXXXXXXX
|       |  ^ start
|       |   ____
| WRITE:| XX    XXXXXX
|       |    ___
| DATA: | XXX   XXXXX
|       | ______  ____
| CLK:  |       __
|       |         ^ ready
```


`Address` changes, the output changes after `3 tau`, independently of the `Clock`. Since `Load`
of each individual register (here called `Write`) is AND'ed with the address decoder, compared to
a single register, the RAM needs `Address` to be ready `3 tau` before `Load` is asserted.


## Class DCSComponentArray

Generates an array of identical components.


## Class DCSRegister1BitWithEnable


#### Pinout
```
In 0 - Data in
In 1 - Clock
In 2 - Clear
In 3 - Preset
In 4 - Load
In 5 - Enable

Out 0 - Data out
```


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


`Load` must be asserted at least `3 tau` before `Clock`'s falling edge. Data` must be stable at
least `2 tau` before `Clock`'s falling edge. `Data` and `Load` have to both be stable for at least
`1 tau` after `Clock`'s falling edge. `Clear` and `Preset` work the same as in the SR latch. Use
them with `Enable` low.


## Class DCSClockDivider

This clock divider (by 2) is mainly meant to be used as a building block for counters.
The minimum clock period is 10 (5 high + 5 low) taus.

`Data in` and `Load` must be stable for at least `4 tau` before and `1 tau` after `Clock`'s
rising edge. The resulting output is displayed `5 tau` after that rising edge.
`Clear` and `Preset` are directly connected to the internal JK master-slave. They must
be stable for at least `3 tau` and their effect is visible `3 tau` after they are set.
`Count in` asserts both `J` and `K` in the internal latch with a delay of `2 tau`. Therefore,
it has to remain stable from `3 tau` to `1 tau` before `Clock`'s rising edge while `Load` is low.

`Count out` is high when `Count in` and `Data out` are high, with a delay of `1 tau`. When
connecting several dividers in cascade, this delay is multiplied by the number of dividers. This
has to be taken into account when choosing the clock speed.

#### Pinout
```
In 0  - Data in
In 1  - Load
In 2  - Clock
In 3  - Clear
In 4  - Preset
In 5  - Count in

Out 0 - Data out
Out 1 - !Data out
Out 2 - Count out
```



## Class DCSNand

NAND gate


## Class DCSDFlipFlop


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


`Data` needs to be ready not later than the time of `Clock`'s assertion.
`Data` and `Clock` must be stable at least `2 tau`.
The output is stable after `4 tau` from the change in the input


## Class DCSOutput

This component has no logical functions but is used to connect any floating output.
Unconnected outputs generate errors!
Also, by naming the used instance of this class, the connected input is probed and hence it can
be displayed.


## Class DCSSRLatch

SR latch.

#### Pinout
```
In  0 - Reset
In  1 - Set
Out 0 - Q
Out 1 - !Q
```



## Class DCSMux2to1

2 to 1 multiplexer

#### Pinout
```
In 0  - Data in 0
In 1  - Data in 1
In 2  - Selector

Out 0 - Data out 0
```



## Class DCSNor

NOR gate


## Class DCSRegister1Bit


#### Pinout
```
In 0 - Data in
In 1 - Clock
In 2 - Clear
In 3 - Preset
In 4 - Load

Out 0 - Data out
```


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


`Load` must be asserted at least `3 tau` before `Clock`'s falling edge.
`Data` must be stable at least `2 tau` before `Clock`'s falling edge.
`Data` and `Load` have to both be stable for at least `1 tau` after `Clock`'s falling edge.
`Clear` and `Preset` work the same as in the SR latch.


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
`compB.getNumOfInPins()`, say `N`, the easiest way to perform the connection is by using the
method

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
`compB`. If this is not the desired order or the pin numbers do not match it is possible to
connect one pin at a time using

```
void connect(DCSComponent* const to, uint16_t outPinNum, uint16_t inPinNum, const std::string&
probeName = "");
```

In addition, one can select a range of output pins to connect to a range of input pins using

```
void connect(DCSComponent* const to, DCSPinNumRange outPinNumRange, DCSPinNumRange
inPinNumRange, const std::vector<std::string>& probeNames = {});
```


## Class DCSNot

NOT gate


## Class DCSDFlipFlopAsyncSR

D Flip-flop with asynchronous Set and Reset

#### Pinout
```
In 0   - Data
In 1   - Clock
In 2   - Reset
In 3   - Preset

Out 0  - Q
Out 1  - !Q
```



## Class DCSEngine

Static class providing


## Class DCSClockSignal

Generates a square wave with period 2 * `halfPeriod`


## Class DCSRegister8BitsWithEnable

8-bit register made up of 8 1-bit registers sharing the same control signals

#### Pinout
```
In 0    - Data in 0
In 1    - Data in 1
In 2    - Data in 2
In 3    - Data in 3
In 4    - Data in 4
In 5    - Data in 5
In 6    - Data in 6
In 7    - Data in 7
In 8    - Clock
In 9    - Clear
In 10   - Preset
In 11   - Load
In 12   - Output Enable

Out 0   - Data out 0
Out 1   - Data out 1
Out 2   - Data out 2
Out 3   - Data out 3
Out 4   - Data out 4
Out 5   - Data out 5
Out 6   - Data out 6
Out 7   - Data out 7
```



## Class DCSNand3

NAND gate with 3 inputs


## Class DCSArbitrarySignal

Generates a binary signal for use as input signal. Instances of this class are created by
DCSClockSignal and DCSInput classes. The user should not use this class directly.


## Class DCSMemoryProgrammer


