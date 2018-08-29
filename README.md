## How to use PTABen

PTABen is a micro-benchmark suite designed for validating various pointer analysis algorithms for C and C++ programs. It includes around 400 hand-written programs and code snippets from real programs. PTABen provides flexible and extendable interfaces for users to add their own tests for validating the correctness of different pointer/alias analyses.


1. Download the whole test suite "PTABen" and put it under the root directory of [SVF](https://github.com/unsw-corg/SVF)
2. Set up environment before runing test cases.
```
   cd $SVFHome
   . ./setup
   cd PTABen
   ./runtest.sh (or ./singlerun.sh basic_c_tests/global-funptr.c)
```
3. "singlerun.sh" provides a simple way to test an analysis (e.g., wpa -ander) given a single program file
4. "runtest.sh" tests an analysis (e.g., wpa -ander) for a set of micro-benchmarks under a specific folder (e.g., basic_c_tests)
   (Note that you can modify variable "TestFolders" and "TestScripts" in "runtest.sh" to specify which folder and what analysis to be tested.)

| Folder       | Description           | 
| ------------- |:-------------:|
|basic_c_tests | basic test cases for C programs (flow-insensitive and field-sensitive analysis)|
|basic_cpp_tests | basic test cases for C++ programs (flow-insensitive and field-sensitive analysis) |
|fs_tests | flow-sensitive tests|
|cs_tests | context-sensitive tests|
|path_tests | path-sensitive tests|
|complex_tests | complex test cases simplified from real programs|
|mta | multithreaded test cases|
|mem_leak | memory leak test cases|
|scripts | scripts to run the tests|


