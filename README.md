# DCS
Digital circuit simulator - from logic gates up

Inspired by the work of [Ben Eater](https://www.youtube.com/watch?v=HyznrdDSSGM&list=PLowKtXNTBypGqImE405J2565dvjafglHU) and not having the possibility to follow his work with hardware, I have decided to write a circuit simulator and build on top of it a processor. I am trying to take into account the time dependency of the system evolution. However, in real hardware, the state change of every component depends on many factors such as the technology in use, noise, imperfections, and so on. It would be out of the scope of this project trying to simulate all these factors. As a good compromise, I define the unit delay `tau` as the maximum delay that any of the elementary logic gates (and, or, not, nand, nor, etc.) can exhibit. Time diagrams and constraints are based on the value of `tau` which can be seen as a free parameter whose value cannot be established a priori. Time itself is therefore discretized in steps of length `tau`.

Examples of how to use the component library are in the main.cpp file.

If you have questions or want to contribute to this project feel free to contact me.

Antonio.

## How to build (Mac and Linux)
You are welcome to build the project the way you prefer. However, you can also use the tool provided here.
#### Generate a Makefile file
1. ```makeMakefile.sh```
2. ```make [OPT=<x>] [OUT=<executable_file_name>]```

`<x> = 0, 1, 2, or 3` is the optimization level. ```OPT``` not specified is equivalent to ```OPT=0```

`executable_file_name` is the name of the executable file, which will be placed in the `./build` folder. The default name is `out`

The compiled object files will be located in `./build/objects`.

#### Example:
```
make OPT=2 OUT=test # produces /build/test with optimization level 2
```
#### Known issue
Before recompiling with different optimization level it is necessary to run `make clean` or the old object files will be reused.