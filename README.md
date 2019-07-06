# CRC Implementation

CRC algorithms in C++, covered by tests.

## Test Suites

gtest has been added to this project.
To run test suites, first build executables:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Then run tests using either

```bash
ctest
```
to run all tests

or

```bash
./bin/unit_tests_1 
# run tests in this way will have relatively more pretty output from terminal, 
# as well as some profiling info
# for convenience (below line is the preferred way to run tests):
cmake .. && cmake --build . && ./bin/your_executable_binary_name
```
to run individual tests.

You can also use regex to specify tests to run:
```bash
ctest -R regex
# e.g.
# you have a test executable named ``Arbitrary_TestSortLinearTime``, then you can run it use:
# ``ctest -R Arbitrary*`` 
```

For convenience, copy below to terminal when first running test:
```bash
rm -rf build && mkdir build && cd build && cmake .. && cmake --build . && ctest
```
To avoid downloading google test each time you run test, do not ``rm -rf build/``.
So just make sure you are in the ``build/`` dir, then 
```shell
cmake .. && cmake --build . && ctest
```
## Lib

``class Crc8{...}`` in ``Lib/Crc8/Crc8.h`` is a naive implementation calculating the 
checksum bit by bit for one-byte input data. It is too slow for real world application 
where the message is typically much larger than just a few bits.

## References

1. [A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS](http://www.ross.net/crc/download/crc_v3.txt)
2. [Understanding CRC](http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html)
