## How to use Test-Suite

Test-Suite is a micro-benchmark suite designed for validating various static analysis algorithms (particularly pointer analyses and static bug checkers) developed in SVF. It includes around 400 hand-written programs and code snippets from real programs. Test-Suite provides flexible and extendable interfaces for users to add their own tests for validating the correctness of different static analyses.


Download SVF and execute the following commandline under SVF's root directory
```
./build.sh
```

The following gives the Test-Suite's folders and the corresponding SVF's options for validation.
| Folder       |  SVF option | Description        |
|--------------|--------------------|:------------------:|
|basic_c_tests |   wpa -ander -stat=false | basic test cases for C programs (flow-insensitive and field-sensitive analysis)|
|basic_cpp_tests | wpa -ander -stat=false | basic test cases for C++ programs (flow-insensitive and field-sensitive analysis) |
|fs_tests |   wpa -fspta -stat=false | flow-sensitive tests|
|cs_tests |  dvf -cxt -print-pts=false -stat=false | context-sensitive tests|
|path_tests |   | path-sensitive tests|
|complex_tests | wpa -ander -stat=false | complex test cases simplified from real programs|
|mta |  | multithreaded test cases|
|mem_leak |   saber -leak -valid-tests -mempar=inter-disjoint -stat=false | memory leak test cases|


