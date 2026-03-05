# NoDefaultLib

Currently just a proof of concept for a no default library build written in Visual C++, build system CMake. The goal is to be able to build an executable with a very small footprint size, currently around 5k, and without any of the other standard libraries like `std` or `crt`. 
Available uses for this could be for embedded Windows systems, installer technology, or for educational purposes to learn how the Windows API works without the abstraction of the standard library.