
<div align="center">

<h1>Simple Heap Memory Pool</h1>

![License: MIT](https://img.shields.io/badge/license-GPL3-green.svg)


</div>

<br>

A simple heap memory pool implementation in a modularized layout, ready to add to your firmware/embedded projects. Manages memory in $O(1)$-time using
a simple dynamic stack.

## Project Structure

```bash
.
├── bin/            # Compiled executables
├── src/            # Source files
├── include/        # Header files
├── Makefile        # Build configuration
└── README.md
```

## Getting Started

### Prerequisites

- GCC compiler
- Make

### Building the Project

To build the test program just run

```bash
make all
```

in your terminal: the executable will be located in the `bin/` directory.

### Running the Program

After building the project you can run the executable from `bin/`.
With `make` you can simply run

```bash
make run
```

in your terminal.

### Cleaning Up

To remove build artifacts:

```bash
make clean
```

## License

GPL3