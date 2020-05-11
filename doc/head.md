# DCS
## Digital circuit simulator - from logic gates up

Inspired by the work of [Ben Eater](https://www.youtube.com/watch?v=HyznrdDSSGM&list=PLowKtXNTBypGqImE405J2565dvjafglHU) and not having the possibility to follow his work with hardware, I have decided to write a circuit simulator and build on top of it a processor.

In this project, the time dependency of the system evolution is considered. However, in real hardware, the state change of every component depends on many factors such as the technology in use, noise, imperfections, and so on. It would be out of the scope of this project trying to simulate all these factors. As a good compromise, the unit delay `tau` is defined as the maximum propagation delay that any of the elementary logic gates (`AND`, `OR`, `NOT`, `NAND`, `NOR`, etc.) can exhibit. Time diagrams and constraints are based on the value of `tau` which can be seen as a free parameter whose value cannot be established a priori. <u>Time itself is therefore discretized in steps of length `tau`.</u>

Examples of how to use the component library are located in `./scr/Tests` folder.

---

## How to build (Mac and Linux)
You are welcome to build the project the way you prefer. However, you can also use the tool provided here.
### Generate a Makefile file
To generate the `Makefile`, from the project directory, run

```
bin/makeMakefile.sh
```
> This script must be run every time you add, move, or remove a `.cpp` or `.hpp` project file.
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
make                  # produces ./build/out-0
make OPT=2 OUT=test   # produces ./build/test-2 with optimization level 2
```
In addition, you can choose to build and run using

```
bin/build-run.sh [<TEST_NUMBER>]              # build and run <TEST_NUMBER>
bin/build-run-save.sh [<TEST_NUMBER>]         # build and run and save the output of <TEST_NUMBER>
```

If `<TEST_NUMBER> (=0, 1, ..., N)` is specified, the corresponding test will be run right after compilation. Check `src/main.cpp` to see the list of tests available. If N is not specified, the default test is run.

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
Two small web applications are provided to display the produced data in a more readable form. Two kinds of data are produced, as described in this section along with their corresponding data viewer.

### Logic analyzer
The application outputs to the standard out. By running

```
bin/build-run-save.sh <TEST_NUMBER> <OPTIMIZATION_LEVEL>
```
the output is `tee`'d to a file entitled `test-n<TEST_NUMBER>-O<OPTIMIZATION_LEVEL>.log`, stored in `./gui/logic-analyzer/assets/`. 
To visualize the data,

- open `./gui/logic-analyzer/index.html` or run `./bin/run-la.sh` from the project directory
- click on `Open files...` in the web GUI
- select one or more files from `./gui/logic-analyzer/assets/` to load them
- use the dropdown menu to select the file output you want to display

 At the time of writing, the interface looks as in the following figure

![web-gui-image](https://github.com/antonioastorino/DCS/blob/master/doc/images/web-gui-0.png)

The GUI allows to

- set the horizontal and vertical scaling factors using the `H-zoom` and `V-zoom` sliders, respectively
- scroll left-right by using the `H-Scroll` slider
- scroll up-down by using the regular mouse wheel
- refresh the image without refreshing the page by clicking on `Refresh` - very useful if you re-build and want to see the updated result from the same file.
- where applicable, visualize the data as separate signals or in single line labeled with the corresponding hexadecimal representation. To switch from one visualization to the other, click on `Go binarly/Go hexadecimal` toggle.

### Performance analyzer
When running any test, the program produces some time measurements by means of the `DCSTimer` class. The data is saved as `./gui/performance-analyzer/assets/profileFile-<TEST_NUMBER>`. The introduced overhead is minimal and therefore this tool is active by default. However, if you prefer to disable it, just set `PROFILING` equal to `0` in `DCSTimer.hpp`.

In order to display the produced data,

- open `./gui/performance-analyzer/index.html` or run `./bin/run-pa.sh` from the project directory
- click on `Open files...` in the web GUI
- select one or more files from `./gui/performance-analyzer/assets/` to load them
- use the dropdown menu to select the file output you want to display

 At the time of writing, the interface looks as in the following figure

![web-gui-image](https://github.com/antonioastorino/DCS/blob/master/doc/images/web-gui-1.png)

The GUI allows to

- set the horizontal scaling factor using the slider above the figure
- pan left-right by dragging the diagram with the mouse
- zoom in/out the center of the graph by using the mouse wheel
- refresh the image without refreshing the page by clicking on `Refresh` - very useful if you re-build and want to see the updated result from the same file.
- visualize the data on separate lines or a single line (the former for overlapping measurements as in the example below). To switch from one visualization to the other, click on `Expand/Collapse` toggle.

---

#### Known issue
If the the window size clips the bottom of the canvas, the scroll bar appears but scrolling up/down using the mouse wheel conflicts with the zoom functionality.
##### Workaround
Zoom first and scroll by dragging the scroll bar or scale down vertically the graph (using the slider) to fit the window.

---

> NOTE 1: I haven't documented `DCSTimer` class yet as it is still under development.

> NOTE 2: The timer class supports multi-threading, although my tests have shown that this project would not benefit for using such a technique. 

> IMPORTANT: do not to use this profiling tool inside a recursive function as it generates misleading results!

---