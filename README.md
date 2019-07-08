# CRC

CRC (Cyclic Redundancy Check) algorithms implemented in C++.

1. Bitwise, Bytewise-Non-Table, and Bytewise-Table-Driven algorithms for CRC-8, CRC-16 and CRC32.
2. The CRC algorithm in ``VTM4.0`` has been extracted as ``CrcXVTM4`` under ``src/Lib`` directory.
3. Each Lib is covered by test cases, including Lib ``CrcXVTM4``.

## Usage 
Clone the project, from project root dir, run tests:
```bash
mkdir build && cd build && cmake .. && cmake --build . && ctest
```

All tests should pass.

## References

1. [A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS](http://www.ross.net/crc/download/crc_v3.txt)
2. [Understanding CRC](http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html)
4. [How is crc32 checksum calculated](https://stackoverflow.com/questions/2587766/how-is-a-crc32-checksum-calculated)
   