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
bin/prj-build-run.sh -n<PRJ_NUM> [-o<OPT_LEVEL>]        # build and run project number <PRJ_NUM> with optimization level <OPT_LEVEL>
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
bin/test-build-run.sh -n<TEST_NUM> [-o<OPT_LEVEL>]        # build and run test number <TEST_NUM> with optimization level <OPT_LEVEL>
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
