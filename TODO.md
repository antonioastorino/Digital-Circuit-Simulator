[ ] make Component->initialized private
[ ] check if it is necessary to know who has updated a component whose input is connected to a tristate component
[ ] change this:

```
std::string message;
 if (wire->getOutVal())
     message = "1";
 else
     message = "0";
 DCSLog::output(wire->getProbeName(), message);
```
[ ] Add MODE to Makefile for release
[ ] Fix makefile that generates `.out-` file