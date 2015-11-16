## How to use micro-benchmarks

1. Download the whole test suites "PTABen" and put it under the root directory of [SVF](https://github.com/unsw-corg/SVF)
2. "singlerun.sh" provides a simple way to test an analysis (e.g., wpa -ander) given an single program file
3. "runtest.sh" tests an analysis (e.g., wpa -ander) for a set of micro-benchmarks under a specific folder (e.g., fi_tests)
   (Note that you can modify variable "TestFolders" and "TestScripts" in "runtest.sh" to specify which folder and what analysis to be tested.)

| Folder       | Description           | 
| ------------- |:-------------:|
|fi_tests | flow-insensitive tests|
|fs_tests | flow-sensitive tests|
|cs_tests | context-sensitive tests|
|path_tests | path-sensitive tests|
|complex_tests | complex test cases simplified from real programs|
|mta | multithreaded test cases|
|mem_leak | memory leak test cases|
|scripts | scripts to run the tests|


