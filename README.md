## How to use PTABen

PTABen is a micro-benchmark suite designed for validating various pointer analysis algorithms for single- and multi-threaded C and C++ programs. It includes around 450 hand-written programs and program segments from real programs. PTABen provides flexible and extendable interfaces for users to add their own tests for validating the correctness of different pointer/alias analyses.


1. Download the whole test suite "PTABen" and put it under the root directory of [SVF](https://github.com/unsw-corg/SVF)
2. Set up environment before runing test cases.
```
   cd $SVFHome
   . ./setup
```
3. "singlerun.sh" provides a simple way to test an analysis (e.g., wpa -ander) given a single program file
4. "runtest.sh" tests an analysis (e.g., wpa -ander) for a set of micro-benchmarks under a specific folder (e.g., fi_tests)
   (Note that you can modify variable "TestFolders" and "TestScripts" in "runtest.sh" to specify which folder and what analysis to be tested.)

| Folder       | Description           | 
| ------------- |:-------------:|
|fi_tests | flow-insensitive tests|
|fs_tests | flow-sensitive tests|
|cs_tests | context-sensitive tests|
|path_tests | path-sensitive tests|
|cpp_tests | test cases for C++ programs|
|complex_tests | complex test cases simplified from real programs|
|mta | multithreaded test cases|
|mem_leak | memory leak test cases|
|scripts | scripts to run the tests|


