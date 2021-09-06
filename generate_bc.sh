#!/bin/sh
# Generate bitcode for the .c/.cpp tests in $test_dirs.

sysOS=`uname -s`

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
bc_path="$root/test_cases_bc"

if [[ $sysOS == "Linux" ]]
then

########
# Remove previous bc folder and create a new one.
########

git rm -rf "$bc_path"
mkdir -p "$bc_path"

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
    if test $td == "mem_leak"
    then
        $compiler -Wno-everything -S -emit-llvm -fno-discard-value-names -g -I"$root" "$c_f" -o "$bc_f"
    else
        $compiler -Wno-everything -S -emit-llvm -fno-discard-value-names -I"$root" "$c_f" -o "$bc_f"
    fi
    #llvm-as "$bc_f" -o "$bc_f"
    opt -S -mem2reg "$bc_f" -o "$bc_f"
  done
done

echo "$0: Compiling diff_tests unit test"
cd src/diff_tests
g++ -o diff_tests_linux diff_tests.cpp
cd ../..
diff_exe_path=diff_tests
if [ ! -d "$diff_exe_path" ]
then
    mkdir -p "$diff_exe_path"
fi
mv src/diff_tests/diff_tests_linux $diff_exe_path/diff_tests_linux
fi

# build diff_tests for osx
if [[ $sysOS == "Darwin" ]]
then
    cd src/diff_tests
    g++ -o diff_tests_osx diff_tests.cpp
    cd ../..
    diff_exe_path=diff_tests
    if [ ! -d "$diff_exe_path" ]
    then
        mkdir -p "$diff_exe_path"
    fi
    mv src/diff_tests/diff_tests_osx $diff_exe_path/diff_tests_osx
fi
