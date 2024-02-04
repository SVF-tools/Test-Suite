#!/bin/sh
# Generate bitcode for the .c/.cpp tests in $test_dirs.

sysOS=$(uname -s)

test_dirs="
  basic_c_tests
  basic_cpp_tests
  complex_tests
  cpp_types
  cs_tests
  fs_tests
  mem_leak
  double_free
  mta
  non_annotated_tests
  path_tests
  objtype_tests
"

root=$(cd "$(dirname "$0")"; pwd)
bc_path="$root/test_cases_bc"

if [[ $sysOS == "Linux" ]];then

########
# Remove previous bc folder and create a new one.
########

git rm -rf "$bc_path"
mkdir -p "$bc_path"

########
# Loops through each folder in test_dirs.
########
for td in $test_dirs; do

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
  for c_f in "$full_td/"*; do

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
    if [ "$bc_f" -nt "$c_f" ]; then
        continue
    fi

    ########
    # Set up the compiler to clang if the file extension is c else clang++.
    ########
    compiler=""
    if [ "$ext" = "c" ]; then
        compiler="clang"
    else
        compiler="clang++"
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
    opt -S -p=mem2reg "$bc_f" -o "$bc_f"
  done
done

fi