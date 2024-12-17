# Advent of Code 2024

[![Build](https://github.com/FrederikTobner/AdventOfCode2024/actions/workflows/Build.yaml/badge.svg)](https://github.com/FrederikTobner/AdventOfCode2024/actions/workflows/Build.yaml)
[![Test](https://github.com/FrederikTobner/AdventOfCode2024/actions/workflows/Test.yaml/badge.svg)](https://github.com/FrederikTobner/AdventOfCode2024/actions/workflows/Test.yaml)
[![Benchmarks](https://github.com/FrederikTobner/AdventOfCode2024/actions/workflows/Benchmarks.yaml/badge.svg)](https://github.com/FrederikTobner/AdventOfCode2024/actions/workflows/Benchmarks.yaml)

Solutions for the [Advent of Code 2024](https://adventofcode.com/2024) written in C++.

![Merry Christmas](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExd3NoNjJ6eGtiZmhrYmtibnI4dnBzd3BpOWswMjh0ODlxMWwybGE1dyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/damYg6Mana2CHXfuz5/giphy.gif)

Uses [CMake](https://cmake.org/) as the build system and the [C++ 23 standard.](https://en.cppreference.com/w/cpp/23)
Requires at least CMake 3.24 and a C++23 compliant compiler (GCC 13.1 or MSVC 17.12.1).
Some of the features used in the code are not implemented in the versions of GCC available under ubuntu and macOS, so some compatibility layers have been created to make the code compile with GCC 13.1.

## Tests

The tests are written using the [GoogleTest](https://github.com/google/googletest) framework
To build and run the tests, you need to enable the `BUILD_TESTS` option in CMake, when configuring the project.

## Performance Tests

The performance tests are written using the [GoogleBenchmark](https://github.com/google/benchmark) framework.
To build and run the performance tests, you need to enable the `BUILD_BENCHMARKS` option in CMake, when configuring the project.

## Layout

Every day has three subdirectories and build targets:

- `src`: Contains the source code for the solution. Only the main function is in this directory.
- `lib`: Contains the source code for the library that is used by the solution.
- `test`: Contains the source code for the testing the solution in the lib directory.
- `benchmark`: Contains the source code for benchmarking the solution in the lib directory.
