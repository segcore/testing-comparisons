# Segcore Testing

## Results

```
t1:    0.063s, 22 kB
t1000: 0.134s, 73 kB

       71 ms per 1000 asserts

f1-f100: 0.510s per 100 files (in parallel)
```

This header is intended to be used with separate executable test binaries,
and use a test runner such as ctest to run them all to gather results.
This means that each test is separately linked, in contrast to many other
testing frameworks. As such, this CMakeLists operates this way.

## Setup

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

touch t1.c; time cmake --build build
    # real    0m0.063s
    # user    0m0.025s
    # sys     0m0.038s

touch t1000.c; time cmake --build build
    # real    0m0.134s
    # user    0m0.092s
    # sys     0m0.042s

touch files/*; time cmake --build build
    # real    0m0.510s
    # user    0m3.077s
    # sys     0m1.991s

ctest --test-dir build
    # Total Test time (real) =   0.22 sec
```
