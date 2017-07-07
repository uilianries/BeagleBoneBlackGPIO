# BeagleBoneBlackGPIO

[![Build Status](https://travis-ci.org/uilianries/BeagleBoneBlackGPIO.svg?branch=master)](https://travis-ci.org/uilianries/BeagleBoneBlackGPIO) [![codecov.io](https://codecov.io/github/uilianries/BeagleBoneBlackGPIO/coverage.svg?branch=master)](https://codecov.io/github/uilianries/BeagleBoneBlackGPIO?branch=master) [![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

## Synopsis

This project is a dedicated library for access GPIO on the BeagleBone Black.
The library provide each pin as a stream, and it can use as input or output.

## Code Example

Show what the library does as concisely as possible, developers should be able to figure out **how** your project solves their problem by looking at the code example. Make sure the API you are showing off is obvious, and that your code is short and concise.

```cpp
#include <thread>
#include <chrono>

#include "bbbgpio/stream.hpp"

int main()
{
    bbb::gpio::ostream ogpio{66};  // Open GPIO 66 as output

    ogpio << bbb::gpio::pin_level::high;  // Set GPIO 66 to high level
    {
        // Do something
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    ogpio << bbb::gpio::pin_level::low;   // Set GPIO 66 to low level

    bbb::gpio::istream igpio{67};  // Open GPIO 67 as input
    bbb::gpio::pin_level gpio_lvl;

    igpio >> gpio_lvl;  // Read current level on GPIO 67

    // bbb::gpio uses RAII

    return 0;
}

```

## Motivation

There are others libraries for GPIO on BBB, however, none of them give access as a file stream.

## Installation

1) Run script/bootstrap.sh to solve your dependencies.
2) Run script/build.sh --install to build and install the project

This project carries some scripts to help these steps, however, you will need some packages:

### Dependencies
- cmake         : Build library and modules
- clang-format  : Format all cpp/hpp file to Webkit style
- clang-tidy    : Linter for all cpp/hpp
- cppcheck      : Static analysis for all cpp/hpp
- valgrind      : Check for memory leak
- doxygen       : Check code documentation
- boost         : Library used in source files

### Internal Scripts
- bootstrap.sh          : Verify depencies as well, try to solve all
- build.sh              : Build the project, libraries and modules
- valgrind.sh		    : Execute Unit Tests and check for memory leak
- linter.sh		        : Check for programmer erros in code
- static-analysis.sh	: Scan code with cppcheck
- doxygen.sh	        : Provide project documentation
- format.sh	            : Format all sources files to Webkit style
- pre-commit		    : Verify change code, with linter and cppcheck, before to commit

The build process is very simple, just run:
- script/build.sh

The app build/test/test_gpio will be created. It runs all unit tests. You could run under valgrind:
- script/valgrind.sh build/test/test_gpio

## Tests

All tests are executed in [Travis CI](https://travis-ci.org/uilianries/BeagleBoneBlackGPIO)

If you want run in some machine, will need [Boost Test](http://www.boost.org/doc/libs/develop/libs/test/doc/html/index.html)

## Contributors

Uilian Ries <uilianries@gmail.com>

## License

The underlying source code is licensed under the [MIT license](http://opensource.org/licenses/mit-license.php).
