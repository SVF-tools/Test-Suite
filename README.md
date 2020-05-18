## How to use Test-Suite

Test-Suite is a micro-benchmark suite designed for validating various static analysis algorithms (particularly pointer analyses and static bug checkers) developed in SVF. It includes around 400 hand-written programs and code snippets from real programs. Test-Suite provides flexible and extendable interfaces for users to add their own tests for validating the correctness of different static analyses.


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

| Folder       | Script | SVF option | Description        |
|--------------|--------|------------|:------------------:|
|basic_c_tests | testwpa.sh | wpa -ander -stat=false | basic test cases for C programs (flow-insensitive and field-sensitive analysis)|
|basic_cpp_tests | | | basic test cases for C++ programs (flow-insensitive and field-sensitive analysis) |
|fs_tests | testwpa.sh | wpa -fspta -stat=false | flow-sensitive tests|
|cs_tests | testdvf.sh | dvf -cxt -print-pts=false -stat=false | context-sensitive tests|
|path_tests | NA | | path-sensitive tests|
|complex_tests | | | complex test cases simplified from real programs|
|mta | | | multithreaded test cases|
|mem_leak | testsaber.sh | saber -leak -valid-tests -mempar=inter-disjoint -stat=false | memory leak test cases|
|scripts | | | scripts to run the tests|


