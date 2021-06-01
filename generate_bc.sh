#!/bin/sh
# Generate bitcode for the .c/.cpp tests in $test_dirs.

test_dirs="
  basic_c_tests
  basic_cpp_tests
  complex_tests
  cpp_types
  cs_tests
  fstbhc_tests
  fstbhc_tests/fs_tests
  fs_tests
  mem_leak
  mta
  non_annotated_tests
  path_tests
"

root=$(cd "$(dirname "$0")"; pwd)
########
# Check whether the test case bc folder exists.
########
bc_path="$root/test_cases_bc"
if [ ! -d "$bc_path" ]
then
    mkdir -p "$bc_path"
fi

########
# Loops through each folder in test_dirs.
########
for td in $test_dirs
do

  ########
  # Creates a directory for each listed folder.
  ########
  bc_td="$bc_path/$td"
  mkdir -p "$bc_td"

  ########
  # Full path to the test dir.
  ########
  full_td="$root/src/$td"

  ########
  # Loops through each file within the folder.
  ########
  for c_f in "$full_td/"*
  do

    ########
    # Obtains the text after the '.'.
    ########
    ext=${c_f##*.}
    
    ########
    # We only look for .c/.cpp files. Check $ext = $f in case the filename is c/cpp.
    ########
    if [ \( "$ext" != "cpp" -a "$ext" != "c" \) -o "$ext" = "$f" ]
    then
        continue
    fi

    ########
    # The output .bc file name.
    ########
    bc_f="$bc_td/`basename "$c_f"`.bc"

    ########
    # If the .bc is newer than the .c/.cpp, then no need to compile.
    ########
    if [ "$bc_f" -nt "$c_f" ]
    then
        continue
    fi

    ########
    # Set up the compiler to clang if the file extension is c else clang++.
    ########
    compiler=""
    if [ "$ext" = "c" ]
    then
        compiler="clang"
    else
        compiler="clang++"
    fi

    ########
    # If the test directory is an fstbhc directory, use ctir Clang.
    ########
    if expr "$td" : "^fstbhc" > /dev/null
    then
        ########
        # If the user hasn't set $SVF_CTIR, they don't want to build ctir tests.
        ########
        if [ -z "$SVF_CTIR" ]
        then
            continue
        elif [ ! -d "$CTIR_DIR" -o ! -r "$CTIR_DIR/$compiler" ]
        then
            echo "$0: expected \$CTIR_DIR (= '$CTIR_DIR') to point to ctir compilers; skipping $c_f"
            continue
        fi
        compiler="$CTIR_DIR/$compiler -ctir"
    fi

    echo "$0: Compiling '$c_f'"
    echo "$0:        to '$bc_f'"

    ########
    # created a .ll, let's make it .bc, as the filename suggests.
    ########
    $compiler -Wno-everything -S -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    llvm-as "$bc_f" -o "$bc_f"
    opt -mem2reg "$bc_f" -o "$bc_f"
  done
done

echo "$0: Compiling diff_tests unit test"
cd src/diff_tests
g++ -o diff_tests diff_tests.cpp
mkdir ../../test_cases_bc/diff_tests
mv diff_tests ../../test_cases_bc/diff_tests/diff_tests
cd ../..