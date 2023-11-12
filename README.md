# CodeCraftAllocator 

This project is a simple memory allocation manager implemented in C. It provides basic memory allocation and management functions for educational and demonstration purposes. It includes memory allocation (`my_malloc`), deallocation (`my_free`), resizing (`my_realloc`), and memory allocation with zero initialization (`my_calloc`).

## Project Structure

The project consists of the following files:

- `main.c`: The main source code file containing the memory allocation manager implementation.
- `xmake.lua`: The build configuration file for xmake, which specifies how to compile the code using the Clang compiler.

## How to Build and Run

To build and run the project, follow these steps:

1. Ensure you have xmake installed on your system.

2. Clone or download the project to your local machine.

3. Open a terminal and navigate to the project directory.

4. Build the project by running the following commands:
 ```shell
xmake config --mode=debug
 ```
```lua
xmake
```
