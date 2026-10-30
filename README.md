# How to use Test-Suite

Test-Suite is a micro-benchmark suite designed for validating various static analysis algorithms (particularly pointer analyses and static bug checkers) developed in SVF. It includes around 400 hand-written programs and code snippets. Test-Suite provides flexible and extendable interfaces for users to add their own tests for validating the correctness of different static analyses.


Download SVF and execute the following commandline under SVF's root directory. `build.sh` will build SVF and run SVF's analyses against the test cases if Test-suite folder is present.
```
git clone https://github.com/SVF-tools/SVF.git
cd SVF
git clone https://github.com/SVF-tools/Test-Suite
source ./build.sh
cd Release-build
ctest
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
| mem_leak              | saber -leak -valid-tests -mempar=inter-disjoint -stat=false | memory leak test cases   
| double_free           | saber -dfree -valid-tests -stat=false                       | double free test cases                                                            |
| blk_tests             | wpa -ander -blk                                             | scanf outputs under the black-hole pointer model (-blk)                           |
| blk_extapi_tests      | wpa -ander -blk -extapi=(test-only extapi in extapi/)       | annotation-driven scanf handling, using a test-only extapi                        |

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


## Andersen SCC endpoint regressions

`src/andersen_scc_tests/` contains textual LLVM IR regressions for
[SVF issue #1944](https://github.com/SVF-tools/SVF/issues/1944). They check that
Load and Store constraints still propagate when SCC merging rewrites an endpoint
to a non-pointer object representative. Textual IR preserves the constraint graph
shape across compiler versions. Each case uses `MAYALIAS` to require the expected
target and runs with both mutable and persistent points-to storage.

```sh
ctest --test-dir Release-build -R '^wpa_tests/andersen_scc/' --output-on-failure
```

The tests explicitly enable `-ff-eq-base=true` to exercise the Store reproducer.
CTest checks both successful and failed alias-validator output, including builds
with assertions disabled.
