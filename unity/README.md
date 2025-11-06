# Unity

The C testing framework [Unity](https://github.com/ThrowTheSwitch/Unity).

## Results

```
t1:    0.074s, 49 kB
t1000: 0.100s, 73 kB

       36 ms per 1000 asserts

f1-f100: 0.602s for 100 files (in parallel)
```

This framework appears most useful when built as separate executable test binaries,
and use a test runner such as ctest to run them all to gather results.

## Notes

Requires either:
* Manual registration of tests in the main() function.
* Automated registration by generating main implementation file(s) with a `ruby`
  script in the Unity repo.
  * No supplied method to call this from CMake, so takes additional setup,
    and may require more effort to make cross-platform.
  * Sample generated file available in `autogen-sample/`

## Setup

Update git submodules to obtain Unity `git submodule update --init`.

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

touch t1.c; time cmake --build build
    # real    0m0.074s
    # user    0m0.039s
    # sys     0m0.035s

touch t1000.c; time cmake --build build
    # real    0m0.100s
    # user    0m0.059s
    # sys     0m0.041s

touch files/*; time cmake --build build
    # real    0m0.602s
    # user    0m3.294s
    # sys     0m2.279s

ctest --test-dir build
    # Total Test time (real) =   0.22 sec
```

