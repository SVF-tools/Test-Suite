#!/bin/sh
# Generates the add_test(...) required by CMake given a
# directory with tests and the command (minus the actual
# target .bc).

folders=("basic_c_tests" "basic_cpp_tests" "fs_tests" "vfs_tests" "cs_tests" "complex_tests" "mem_leak" "fstbhc_tests" "fstbhc_tests/fs_tests")
commands=("wpa -ander -stat=false" "wpa -ander -stat=false" "wpa -fspta -stat=false" "wpa -vfspta -opt-svfg=false -stat=false" "dvf -cxt -print-pts=false -stat=false" "wpa -ander -stat=false" "saber -leak -valid-tests --mem-par=inter-disjoint -stat=false" "wpa -fstbhc -stat=false" "wpa -fstbhc -stat=false")

root=$(cd "$(dirname "$0")"; pwd)
cd $root

rm -f "CMakeLists.txt"

echo "if(NOT CMAKE_BUILD_TYPE)"  >> "CMakeLists.txt"
echo "    set(CMAKE_BUILD_TYPE Release)" >> "CMakeLists.txt"
echo "endif()" >> "CMakeLists.txt"

for i in "${!folders[@]}";
do
  echo "# ${commands[$i]} (${folders[$i]})" >> "CMakeLists.txt"
  bc_dir_name="test_cases_bc"

  if [[ "${folders[$i]}" == *"fstbhc_tests"* ]]; then
    echo "if (DEFINED ENV{SVF_CTIR})" >> "CMakeLists.txt"
  fi

  for f in ""${folders[$i]}"/"*; do
    # Ignore non-.c/.cpp files.
    ext=${f##*.}
    if [ \( "$ext" != "c" -a "$ext" != "cpp" \) -o "$ext" = "$f" ]; then
      continue;
    fi
    echo "add_test(" >> "CMakeLists.txt"
    echo "  NAME $f" >> "CMakeLists.txt"
    echo "  COMMAND "${commands[$i]}" \${CMAKE_CURRENT_SOURCE_DIR}/$bc_dir_name/$f.bc" >> "CMakeLists.txt"
    echo "  WORKING_DIRECTORY \${PROJECT_SOURCE_DIR}/\${CMAKE_BUILD_TYPE}-build/bin" >> "CMakeLists.txt"
    echo ")" >> "CMakeLists.txt"
    echo "" >> "CMakeLists.txt"
  done
  if [[ "${folders[$i]}" == *"fstbhc_tests"* ]]; then
    echo "endif()" >> "CMakeLists.txt"
    echo "" >> "CMakeLists.txt"
  fi
done

# differential tests -fspta and -vfspta
for f in "fs_tests/"*; do
  # Ignore non-.c/.cpp files.
  ext=${f##*.}
  if [ \( "$ext" != "c" -a "$ext" != "cpp" \) -o "$ext" = "$f" ]; then
    continue;
  fi
  echo "# differential tests fspta - vfspta" >> "CMakeLists.txt"
  echo "add_test(" >> "CMakeLists.txt"
  echo "  NAME differential_test/fspta-vfspta/$f" >> "CMakeLists.txt"
  echo "  COMMAND diff <(wpa -fspta \${CMAKE_CURRENT_SOURCE_DIR}/$bc_dir_name/$f.bc) <(wpa -vfspta \${CMAKE_CURRENT_SOURCE_DIR}/$bc_dir_name/$f.bc)" >> "CMakeLists.txt"
  echo "  WORKING_DIRECTORY \${PROJECT_SOURCE_DIR}/\${CMAKE_BUILD_TYPE}-build/bin" >> "CMakeLists.txt"
  echo ")" >> "CMakeLists.txt"
  echo "set_tests_properties(differential_test/fspta-vfspta/$f PROPERTIES FAIL_REGULAR_EXPRESSION \"AvgTopLvlPtsSize\")" >> "CMakeLists.txt"
  echo "" >> "CMakeLists.txt"
done
