# Boost.Test

## Results

```
t1            5.838s  6621K
t1000         7.503s  7457K
        1.7ms per assert

t1_static     0.788s  1337K
t1000_static  2.396s  2174K
        1.6ms per assert

f1-f100: 10.427s per 100 files (in parallel)
```

71ms for 1000 tests: 71 us per assert

## Setup

- Get Boost (bottom of this readme)
- Build
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

touch t1.cpp; time cmake --build build
    # real    0m5.838s
    # user    0m5.247s
    # sys     0m0.589s

touch t1000.cpp; time cmake --build build
    # real    0m7.503s
    # user    0m6.742s
    # sys     0m0.759s

touch t1_static.cpp; time cmake --build build
    # real    0m0.788s
    # user    0m0.620s
    # sys     0m0.168s

touch t1000_static.cpp; time cmake --build build
    # real    0m2.396s
    # user    0m2.139s
    # sys     0m0.254s

touch files/*; time cmake --build build -t files
    # real    0m10.427s
    # user    1m37.681s
    # sys     0m15.394s

touch files/*; time cmake --build build -t files_static
    # real    0m9.715s
    # user    1m29.818s
    # sys     0m14.925s


```

### Getting Boost

- wget https://archives.boost.io/release/1.89.0/source/boost_1_89_0.tar.bz2
- Extract to boost_extracted
- Build
  ```sh
  cd boost_extracted
  time ./bootstrap.sh --prefix=$PWD/../boost_built/
  # real    0m30.839s
  # user    0m26.790s
  # sys     0m4.016s
  time ./b2
  # real    2m26.626s
  # user    16m22.743s
  # sys     1m57.569s
  time ./b2 install
  # real    1m3.789s
  # user    1m2.754s
  # sys     0m1.565s

  # Total: 4m01s
  ```
