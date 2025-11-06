# Google Test

## Results

```
t1     0.888s, 3007 kB
t1000  2.128s, 3908 kB

       1.2 ms per assert

f1-f100: 10.826 for 100 files (in parallel)
```

## Setup

```sh
time cmake -B build -DCMAKE_BUILD_TYPE=Debug
    # real    0m2.233s
    # user    0m0.446s
    # sys     0m0.426s

time cmake --build build
    # real    0m3.496s
    # user    0m8.305s
    # sys     0m1.501s

touch t1.cpp; time cmake --build build
    # real    0m0.888s
    # user    0m0.705s
    # sys     0m0.183s

touch t1000.cpp; time cmake --build build
    # real    0m2.128s
    # user    0m1.817s
    # sys     0m0.311s

touch files/*; time cmake --build build
    # real    0m10.826s
    # user    1m41.186s
    # sys     0m18.240s


ctest --test-dir build
    # Total Test time (real) =   0.85 sec
```

NOTE: Using the latest commit and their example program does not build.
