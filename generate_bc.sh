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
bc_dir_name="test_cases_bc"
# Check whether the test case bc folder exists.
bc_path="$root/$bc_dir_name"
if [ ! -d "$bc_path" ] ; then
  mkdir -p "$bc_path"
fi

for td in $test_dirs; do
  # Where the resulting bitcode files for this test dir will live.
  bc_td="$bc_path/$td"
  mkdir -p "$bc_td"
  # Full path to the test dir.
  full_td="$root/$td"

  for c_f in "$full_td/"*; do
    ext=${c_f##*.}
    # Only care about .c/.cpp files. Check $ext = $f in case filename is c/cpp.
    if [ \( "$ext" != "cpp" -a "$ext" != "c" \) -o "$ext" = "$f" ]; then
      continue
    fi

    # The output .bc file name.
    bc_f="$bc_td/`basename "$c_f"`.bc"

    # If the .bc is newer than the .c/.cpp, then no need to compile.
    if [ "$bc_f" -nt "$c_f" ]; then
      continue
    fi

    compiler=""
    if [ "$ext" = "c" ]; then
      compiler="clang"
    else
      # Definitely = cpp.
      compiler="clang++"
    fi

    # If the test directory is an fstbhc directory, use ctir Clang.
    if expr "$td" : "^fstbhc" > /dev/null; then
      # If the user hasn't set $SVF_CTIR, they don't want to build ctir tests.
      if [ -z "$SVF_CTIR" ]; then
        continue
      fi

      if [ ! -d "$CTIR_DIR" -o ! -r "$CTIR_DIR/$compiler" ]; then
        echo "$0: expected \$CTIR_DIR (= '$CTIR_DIR') to point to ctir compilers; skipping $c_f"
        continue
      fi

      compiler="$CTIR_DIR/$compiler -ctir"
    fi

    echo "$0: Compiling '$c_f'"
    echo "$0:        to '$bc_f'"

    $compiler -Wno-everything -S -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    # ^ created a .ll, let's make it .bc, as the filename suggests.
    llvm-as "$bc_f" -o "$bc_f"
    opt -mem2reg "$bc_f" -o "$bc_f"
  done
done
