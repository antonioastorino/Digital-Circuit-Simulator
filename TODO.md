[ ] BUG: makeSignal("0XXXX") starts with 1
[X] make V-zoom longer
[X] make Component->initialized private
[ ] check if it is necessary to know who has updated a component whose input is connected to a tristate component
[ ] replace forward declarations in Register1Bit with include 
[ ] create a master clock
[ ] add pin-in-range check in connect()
[X] nothing loaded does not erase the loaded file list
[X] change `</h1>` into `</h2>` in logic analyzer
[X] change this:

```
std::string message;
 if (wire->getOutVal())
     message = "1";
 else
     message = "0";
 DCSLog::output(wire->getProbeName(), message);
```
[ ] Add MODE to Makefile for release
[X] Fix makefile that generates `.out-` file
[X] Retrieve thread ID using

```
uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
```

