# How to use Test-Suite

Test-Suite is a micro-benchmark suite designed for validating various static analysis algorithms (particularly pointer analyses and static bug checkers) developed in SVF. It includes around 400 hand-written programs and code snippets. Test-Suite provides flexible and extendable interfaces for users to add their own tests for validating the correctness of different static analyses.


Download SVF and execute the following commandline under SVF's root directory. `build.sh` will build SVF and run SVF's analyses against the test cases if Test-suite folder is present.
```
git clone https://github.com/SVF-tools/SVF.git
cd SVF
git clone https://github.com/SVF-tools/Test-Suite
source ./build.sh
```

The following gives the Test-Suite's folders and the corresponding SVF's options for validation.
| Folder                |  SVF option                                                 | Description                                                                       |
|-----------------------|-------------------------------------------------------------|:---------------------------------------------------------------------------------:|
| basic_c_tests         | wpa -ander -stat=false                                      | basic test cases for C programs (flow-insensitive and field-sensitive analysis)   |
| basic_cpp_tests       | wpa -ander -stat=false                                      | basic test cases for C++ programs (flow-insensitive and field-sensitive analysis) |
| fs_tests              | wpa -fspta -stat=false                                      | flow-sensitive tests                                                              |
| cs_tests              | dvf -cxt -print-pts=false -stat=false                       | context-sensitive tests                                                           |
| path_tests            |                                                             | path-sensitive tests                                                              |
| complex_tests         | wpa -ander -stat=false                                      | complex test cases simplified from real programs                                  |
| mta                   |                                                             | multithreaded test cases                                                          |
| mem_leak              | saber -leak -valid-tests -mempar=inter-disjoint -stat=false | memory leak test cases                                                            |
| fstbhc_tests          | wpa -fstbhc -stat=false                                     | FSTBHC tests                                                                      |
| fstbhc_tests/fs_tests | wpa -fstbhc -stat=false                                     | FSTBHC tests sourced from fs_tests                                                |

To compile the tests in `fstbhc_tests` and `fstbhc_tests/fs_tests`, [ctir Clang](https://github.com/mbarbar/ctir) is required, which SVF's `build.sh` will download.

## Scripts
Travis CI is used to build all the test cases, It uses `./generate_bc.sh` to do so and then pushes the compiled test cases into master branch.

All tests are specified in `CMakeLists.txt` file. The `CMakeLists.txt` file uses foreach loops to specify tests in bulk. To add new tests append a command and specified folder into the respective commands list and folders list in `CMakeLists.txt`
An example of a test:
```
add_test(
  NAME basic_c_tests/CI-funptr.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/CI-funptr.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
```

For differential testing of two options a C++ script `diff_tests.cpp` is used. This script will run each option, compare the results and output. If the output is 0 then the test passed.

