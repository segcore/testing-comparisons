# Test Timing

How much do testing frameworks cost?

| Framework         | Language      | Base compile time (s) | Compile time for 1000 asserts (s) | Compile time for 100 files (s) |
| ---               | ---           | ---                   | ---                               | ---                            |
| Boost.Test        | C++           | 5.8                   | 7.5 (+1.7)                        | 10.4                           |
| Boost.Test static | C++           | 0.8                   | 2.4 (+1.6)                        |  9.7                           |
| GoogleTest        | C++           | 0.9                   | 2.1 (+1.2)                        | 10.8                           |
| testing.h         | C             | 0.06                  | 0.13 (+0.07)                      |  0.51                          |
| Unity             | C             | 0.07                  | 0.10 (+0.03)                      |  0.60                          |


## Notes

* Building the 100 files is in parallel with ninja
* GoogleTest can expose its individual tests to ctest, so works well stand-alone and with ctest.
* Boost.Test seems intended to just be run directly
* testing.h is intended to be run with a test-runner such as ctest (or `for x in tests/*; do ./$x; done`)
  to supply the additional 'fancy' functionality if required.

## CTest

If using CMake as the build system, adding CTest as a test runner takes very
little effort. Much of the functionality which is built-in to GoogleTest and
Boost.Test is also available in CTest. This means that the testing framework
can be simpler and just focus on testing (which makes it compile faster too).

Some CTest features include:
* Run all tests in one command
* Run a subset of tests
* Run tests in parallel
* Randomize test order
* Test timeouts
* Quiet and verbose modes
* Output JUnit formatted test results
* Repeat tests
* Test cost logging (how long each test takes to run, over many runs)
* Re-run only failed tests
* Submit results to a graphical dashboard
