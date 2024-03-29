# DCS
## Digital circuit simulator - from logic gates up

Inspired by [Ben Eater](https://www.youtube.com/watch?v=HyznrdDSSGM&list=PLowKtXNTBypGqImE405J2565dvjafglHU)'s work, I have decided to write a circuit simulator and build on top of it Ben's 8-bit computer.

In this project, the time dependency of the system evolution is considered. However, in real hardware, the state change of every component depends on many factors such as the technology in use, noise, imperfections, and so on. It would be out of the scope of this project trying to simulate all these factors. As a good compromise, the unit delay `tau` is defined as the maximum propagation delay that any of the elementary logic gates (`AND`, `OR`, `NOT`, `NAND`, `NOR`, etc.) can exhibit. Time diagrams and constraints are based on the value of `tau` which can be seen as a free parameter whose value cannot be established a priori. <u>Time itself is therefore discretized in steps of length `tau`.</u>

Examples of how to use the component library are located in unit tests and project files.

A working program that counts by threes (project number `0`) is loaded and run by my software version of Ben's computer. Here is the assembly code:

```
0: LDI 3   // load 3 in Reg A
1: STA 15  // store 3 in RAM at address 15
2: LDI 0   // load 0 in Reg A
3: ADD 15  // load 3 from RAM (at address 15) in Reg B and store the sum in Reg A
4: OUT 0   // display the output
5: JMP 3   // jump to instruction 3
```
I hope this just ignited your curiosity :)

---

## How to build (Mac only, at the moment)
You are welcome to build the project the way you prefer. However, it is recommended that you use the tool provided in this repository, based upon [this project](https://github.com/antonioastorino/MMF).

### 1. Generate Makefile
Generate `Makefile` by running

```
bin/makeMakefile.sh
```
from the project directory.

### 2. Build and run

I assume `make` and `clang` are already installed on your machine.

#### 2.1. Projects
For all projects, the source code is located in `src/Projects/`. Projects are numbered from `0` to `N-1`, where `N` is the number of projects available.

Compiling and running a project is done by executing

```
bin/prj-build-run.sh -n<PRJ_NUM> -o[<OPT_LEVEL>]        # build and run project number <PRJ_NUM> with optimization level <OPT_LEVEL>
```
`<OPT_LEVEL> = 0, 1, 2, or 3` is the optimization level.

If the project number is omitted or not valid, the list of available projects is prompted. For example, executing

```
bin/prj-build-run.sh
```

produces something like

```
Please add a valid project or test number as a parameter.
Choose one of the following:
#       Title
0       firstProgramPrj
1       fastControlUnitPrj
2       fastZeroFlagProgramPrj
3       noCUComputerPrj
```
If a valid project number is specified, the corresponding project output is displayed, as in the example that follows.

```
% bin/prj-build-run.sh -n1 -o0   # build and run project 1 with optimization level 0              
-------------------------
Fast control unit project
-------------------------
 in:0b00000000    0d out:0b0000000000000000      0d STEP:0
 in:0b00000001    1d out:0b0100000000000100  16388d STEP:14
 in:0b00000010    2d out:0b0001010000001000   5128d STEP:28
 in:0b00000011    3d out:0b0000000000000000      0d STEP:42
 in:0b00000100    4d out:0b0000000000000000      0d STEP:56
 in:0b00000101    5d out:0b0000000000000000      0d STEP:70
 in:0b00000110    6d out:0b0000000000000000      0d STEP:84
 in:0b00000111    7d out:0b0000000000000000      0d STEP:98
 in:0b00001000    8d out:0b0000000000000000      0d STEP:112
 in:0b00001001    9d out:0b0100000000000100  16388d STEP:126
 ...
```
#### 2.2. Tests
Tests are located at the bottom of `.cpp` files. Tests are numbered from `0` to `M-1`, where `M` is the number of tests available. The `main-test.cpp` file is the entry point. Depending on the selected test number, `main()` will call the corresponding test.

Compiling and running a test is done in the same as for a project, but replacing "prj" with "test":

```
bin/test-build-run.sh -n<TEST_NUM> -o[<OPT_LEVEL>]        # build and run test number <TEST_NUM> with optimization level <OPT_LEVEL>
```
`<OPT_LEVEL> = 0, 1, 2, or 3` is the optimization level.

Once again, if the test number is not valid or not specified, the output is a list of available tests, otherwise the chosen test is build and run.

The output of tests is saved to `gui/logic-analyzer/data/out-test-n<TEST_NUM>.log`. A permanent version of this file is already present in `test/expected` and used to verify that the test output matches the expected one.

### 2.3. Cleaning up

To delete all the artifacts run

```
bin/cleanup.sh
```

This script is always run when `bin/makeMakefile.sh` is called.

## How to display the data
Two small web applications are provided to display the produced data in a more readable form. Two kinds of data are produced, as described in this section, along with their corresponding viewer.

### Logic analyzer
When any test or project is run using `bin/prj-build-run.sh` or `bin/test-build-run.sh`, the output data is saved to a file in `gui/logic-analyzer/data/` folder. To visualize such data

- run `bin/run-la.sh` from the project directory
- click on `Open files...` in the web GUI
- select it (or multiple files) from `gui/logic-analyzer/data/`
- use the dropdown menu to select the file output you want to display

 At the time of writing, the interface looks as in the following figure

![web-gui-image](https://github.com/antonioastorino/DCS/blob/master/doc/images/web-gui-0.png)

The GUI allows to

- set the horizontal and vertical scaling factors using the `H-zoom` and `V-zoom` sliders, respectively;
- scroll left/right by using the `H-Scroll` slider;
- scroll up/down by using the regular mouse wheel;
- refresh the image without refreshing the page by clicking on `Refresh` - very useful if you re-build and want to see the updated result from the same file;
- where applicable, visualize the data as separate signals or in single line labeled with the corresponding hexadecimal representation -click on the `Go binary/Go hexadecimal` toggle to switch from one visualization to the other.

### Performance analyzer
When any test or project is run, the program produces some time measurements by means of the `DCSTimer` class. The data is saved as to a file in `gui/performance-analyzer/data/`. The introduced overhead is minimal and therefore this tool is active by default. However, if you prefer to disable it, just set `PROFILING` equal to `0` in `DCSTimer.hpp`.

In order to display the produced data,

- open run `bin/run-pa.sh` from the project directory
- click on `Open files...` in the web GUI
- select one or more files from `gui/performance-analyzer/data/` to load them
- use the dropdown menu to select the file output you want to display

 At the time of writing, the interface looks as in the following figure

![web-gui-image](https://github.com/antonioastorino/DCS/blob/master/doc/images/web-gui-1.png)

The GUI allows to

- set the horizontal scaling factor using the slider above the figure
- pan left/right by dragging the diagram with the mouse
- zoom in/out the center of the graph by using the mouse wheel
- refresh the image without refreshing the page by clicking on `Refresh` - very useful if you re-build and want to see the updated result from the same file.
- visualize the data on separate lines or a single line (the former, for overlapping measurements as in the example below). To switch from one visualization to the other, click on `Expand/Collapse` toggle.

---

#### Known issue
If the the window size clips the bottom of the canvas, the scroll bar appears but scrolling up/down using the mouse wheel conflicts with the zoom functionality.
##### Workaround: Zoom first and scroll by dragging the scroll bar or scale down vertically the graph (using the slider) to fit the window.

---

> NOTE 1: I haven't documented `DCSTimer` class yet as it is still under development.

> NOTE 2: The timer class supports multi-threading, although my tests have shown that this project would not benefit for using such a technique. 

> IMPORTANT: do not to use this profiling tool inside a recursive function as it generates misleading results.

---
# Component description


## Class DCSALU


ALU capable of adding (A+B) or subtracting (A-B) 8-bit numbers.

#### Pinout
```
In 0   - A 0
In 1   - A 1
In 2   - A 2
In 3   - A 3
In 4   - A 4
In 5   - A 5
In 6   - A 6
In 7   - A 7
In 8   - B 0
In 9   - B 1
In 10  - B 2
In 11  - B 3
In 12  - B 4
In 13  - B 5
In 14  - B 6
In 15  - B 7
In 16  - SU (subtract)

Out 0  - E 0
Out 1  - E 1
Out 2  - E 2
Out 3  - E 3
Out 4  - E 4
Out 5  - E 5
Out 6  - E 6
Out 7  - E 7
Out 8  - Overflow
Out 9  - Zero
```




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




## Class DCSRippleAdder8Bits


8-bit ripple adder

#### Pinout
```
In 0   - A 0
In 1   - A 1
In 2   - A 2
In 3   - A 3
In 4   - A 4
In 5   - A 5
In 6   - A 6
In 7   - A 7
In 8   - B 0
In 9   - B 1
In 10  - B 2
In 11  - B 3
In 12  - B 4
In 13  - B 5
In 14  - B 6
In 15  - B 7
In 16  - Carry in

Out 0  - Sum 0
Out 1  - Sum 1
Out 2  - Sum 2
Out 3  - Sum 3
Out 4  - Sum 4
Out 5  - Sum 5
Out 6  - Sum 6
Out 7  - Sum 7
```




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



## Class DCSComponentArray

Generates an array of identical components.



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
 For example, a signal that starts at 0 and changes after 2 clock cycles and then again after 3
clock cycles can be obtained as follows:

 ```makeSignal({2, 3}, 0, true);```

- assign a signal expressed as a string of bits

 ```
	void makeSignal(std::string signal, bool synch = false);
 ```
	To generate the same signal as in the previous example, you can use

 ```makeSignal("001110"); // without the last zero the signal would stay high```

- assign a square wave

 ```
 void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
 ```

### Initialization with constant signal

```
DCSInput(std::string name, bool initValue);
```




## Class DCSNode


This component provides a single access point to several connections with zero latency. It has
one input and one output. Using this component is essential when building composite components.
For example, assuming to have component `A` composed of 2 basic componets, `A0` and `A1`. Suppose
also that `A0` and `A1` should receive the same input `I`. There is no way for `A` to provide a
single connection to both `A0` and `A1` to the external logic. However, by defining a node `N0`,
`A` can connect `I` to the input of `N0` and connect the output of `N0` to both `A0` and `A1`.

Nodes are also used to create busses and avoid to connect components to each other directly.
Instead, one can connect a node to all commponets' inputs and all (tri-state'd) components'
outputs to a node.



## Class DCSOutput

This component has no logical functions but is used to connect any floating output.
Unconnected outputs generate errors!
Also, by naming the used instance of this class, the connected input is probed and hence it can
be displayed.



## Class DCSTristateBuffer8Bits

Consists of an array of tri-state buffers sharing `Enable`

#### Pinout
```
In 0   - Data in 0
In 1   - Data in 1
In 2   - Data in 2
In 3   - Data in 3
In 4   - Data in 4
In 5   - Data in 5
In 6   - Data in 6
In 7   - Data in 7
In 8   - Enable

Out 0  - Data out 0
Out 1  - Data out 1
Out 2  - Data out 2
Out 3  - Data out 3
Out 4  - Data out 4
Out 5  - Data out 5
Out 6  - Data out 6
Out 7  - Data out 7
```




## Class DCSControlUnit4Bits


#### Pinout
```
In 0    - Clock
In 1    - Reset
In 2    - Address 0
In 3    - Address 1
In 4    - Address 2
In 5    - Address 3

Out 0   - Ctrl 0
Out 1   - Ctrl 1
...
Out 15  - Ctrl 15
```




## Class DCSControlUnit5Bits

The core of this component is a combinatorial logic, represented by the internal PLD. A counter
drives the first 3 bits of the PLD address while the remaining 5 bits are available to the user.
The counter is incremented upon clock rising edge. A register is placed at the output to
synchronize all the output pins. The register is updated upon clock falling edge.

#### Pinout
```
In 0    - Clock
In 1    - Reset
In 2    - Address 0
In 3    - Address 1
In 4    - Address 2
In 5    - Address 3
In 6    - Address 4

Out 0   - Ctrl 0
Out 1   - Ctrl 1
...
Out 15  - Ctrl 15
```




## Class DCSEngine

Static class providing all the functionalities needed to manage the system initialization and
evolution.




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




## Class DCSUpCounterWithLoadAndAsyncSR

N-bit up-counter (N defined upon instantiation) with synchronous load and asynchronous clear and
reset. Internally, there are N clock dividers in cascade.

#### Pinout
```
In 0         - Count enable
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

| LD | CE | CLK | Function
|----|:-----|:----|:--------
|  0 |   0  | X   |  Pause
|  0 |   1  | _/  |  Count
|  1 |   X  | _/  |  Load


`Cout in` follows the rule of input 5 of the first divider. Therefore, it hast to be set
from `3` to `1 tau` before the clock rising edge. However, every `Count in` in the subsequent
dividers is delayed by `1 tau`. In addition, the output byte of the counter is ready `5 tau` after
the clock rising edge. As a consequence, supposing that the expected output is all 1's, the last
`Count in` will be ready `5+N-1 tau` after the clock rising edge and has to be ready `3 tau`
before the next clock rising edge. Therefore, the clock period has to be at least `5+N-1+3 = 7+N
tau`.



## Class DCSAddressDecoder4Bits

Address decoder with a 4-bit input and 256-bit output.

#### Pinout
```
In 0    - Address 0
In 1    - Address 1
In 2    - Address 2
In 3    - Address 3

Out 0   - Decoded in 0 (asserted only when the input is 0000)
Out 1   - Decoded in 1 (asserted only when the input is 0001)
...
Out 16  - Decoded in 16 (asserted only when the input is 1111)
```




## Class DCSAddressDecoder8Bits

Address decoder with an 8-bit input and 256-bit output.

#### Pinout
```
In 0    - Address 0
In 1    - Address 1
...
In 7    - Address 7

Out 0   - Decoded in 0 (asserted only when the input is 00000000)
Out 1   - Decoded in 1 (asserted only when the input is 00000001)
...
Out 255 - Decoded in 255 (asserted only when the input is 11111111)
```




## Class DCSPLD8In16Out

This class implements a Programmable Logic Device (PLD) equivalent to `DCSRam256x16` but, once
programmed, it becomes read-only. Programming a `DCSPLD8In16Out` is done by its initializer,
which requires the configuration data to be passed as an argument. The advantage of using this
class in place of a RAM is that it much faster (the number of logic gates in a RAM is about 75
times that of this PLD). Therefore, the computation time is substantially reduced when using this
PLD. Also, there is no control logic involved, which makes its use much simpler than a RAM.

#### Pinout
```
In 0  - Address 0
In 1  - Address 1
...
In 7  - Address 7

Out 0 - Data out 0
Out 1 - Data out 1
...
Out 15 - Data out 15
```




## Class DCSDisplayNBits






## Class DCSAnd

AND gate



## Class DCSAnd3

AND gate with 3 inputs



## Class DCSAnd4

AND gate with 4 inputs



## Class DCSAnd6

AND gate with 6 inputs as an array of two DCSAnd3 AND'ed together by an AND gate



## Class DCSAnd8

AND gate with 8 inputs as an array of two DCSAnd4 AND'ed together by an AND gate



## Class DCSNand

NAND gate



## Class DCSNand3

NAND gate with 3 inputs



## Class DCSNor

NOR gate



## Class DCSNor3

NOR gate with 3 inputs



## Class DCSNot

NOT gate



## Class DCSOr

OR gate



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
| CLK: | X__  \\  go down any time 2 tau after rising edge
|      |    ^ stored
|      |        _____
| Q:   | _______
|      | ______
|!Q:   |       ______
|      |        ^ ready
```




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



## Class DCSSRLatch

SR latch.

#### Pinout
```
In  0 - Reset
In  1 - Set
Out 0 - Q
Out 1 - !Q
```




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


If `Address` changes, the output changes after `3 tau`, independently of the `Clock`. Since
`Load` of each individual register (here called `Write`) is AND'ed with the address decoder,
compared to a single register, the RAM needs `Address` to be ready `3 tau` before `Load` is
asserted.



## Class DCSRam256x16

Ram module of 16 bytes.

#### Pinout
```
In 0    - Data in 0
In 1    - Data in 1
...
In 15   - Data in 15
In 16   - Address 0
In 17   - Address 1
...
In 23   - Address 8
In 24   - Clock
In 25   - Clear
In 26   - Preset
In 27   - Write
In 28   - Output enable

Out 0   - Data out 0
Out 1   - Data out 1
...
Out 15  - Data out 15
```


#### Time diagram
```
|       |  ____
| ADDR: | X____XXXXXXXX
|       |  ^ start
|       |    ____
| WRITE:| XXX    XXXXXX
|       |     ___
| DATA: | XXXX   XXXXX
|       | _______  ____
| CLK:  |        __
|       |          ^ ready
```


The time diagram is similar to that of Ram16x8. The only difference is in the that `Address`
needs to be prepared `1 tau` earlier because the internal address decoder introduces an extra
`1-tau` delay due to the presence of 8-bit AND gates. The smaller ram's address decoder was using
4-bit AND gates, instead.



## Class DCSRegister16BitsWithEnable

16-bit register consisting an array of 16 1-bit registers sharing the same control signals

#### Pinout
```
In 0    - Data in 0
In 1    - Data in 1
...
In 15   - Data in 15
In 16   - Clock
In 17   - Clear
In 18   - Preset
In 19   - Load
In 20   - Output Enable

Out 0   - Data out 0
Out 1   - Data out 1
...
Out 15  - Data out 15
```




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



## Class DCSRegister4Bits

4-bit register made up of 4 1-bit registers sharing the same control signals

#### Pinout
```
In 0    - Data in 0
In 1    - Data in 1
In 2    - Data in 2
In 3    - Data in 3
In 4    - Clock
In 5    - Clear
In 6    - Preset
In 7    - Load

Out 0   - Data out 0
Out 1   - Data out 1
Out 2   - Data out 2
Out 3   - Data out 3
```




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




## Class DCSRegister8BitsWithEnable

8-bit register consisting of an array of 8 1-bit registers sharing the same control signals

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




## Class DCSMux2To1

2 to 1 multiplexer

#### Pinout
```
In 0  - Data in 0
In 1  - Data in 1
In 2  - Selector

Out 0 - Data out 0
```




## Class DCSArbitrarySignal

Generates a binary signal for use as input signal. Instances of this class are created by
DCSClockSignal and DCSInput classes. The user should not use this class directly.



## Class DCSClockSignal

Generates a square wave with period 2 * `halfPeriod`


