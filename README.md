# DCS
Digital circuit simulator - from logic gates up

Inspired by the work of [Ben Eater](https://www.youtube.com/watch?v=HyznrdDSSGM&list=PLowKtXNTBypGqImE405J2565dvjafglHU) and not having the possibility to work with hardware, I have decided to write a circuit simulator and build on top of it a processor. I am trying to keep the time dependency of the system evolution alive and coherent. However, the state change of every component depends on many factors such as the technology in use, randomness/imperfections, and even how components are connected. Therefore, I define the unit delay `tau` as the maximum delay that any of the elementary logic gate can exhibit. Time diagrams and constraints are based on the value of `tau` which can be seen as a free parameter whose value cannot be established a priori. Time itself is therefore discretized in steps of length `tau`.

If you want to contribute to this project feel free to contact me.

Antonio.
