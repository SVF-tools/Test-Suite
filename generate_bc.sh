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
  ae_overflow_tests
  ae_assert_tests
  ae_nullptr_deref_tests
  ae_recursion_tests
  ae_wto_assert
"


root=$(cd "$(dirname "$0")"; pwd)
bc_path="$root/test_cases_bc"

if [[ $sysOS == "Linux" || $sysOS == "Darwin" || $sysOS =~ "MINGW" || $sysOS =~ "MSYS" ]];then

########
# Remove previous bc files and create a new directory layout, while
# preserving the committed Windows-only bitcode file.
########
preserved_bc="$bc_path/mem_leak/leak_win_heap.c.bc"
if [ -d "$bc_path" ]; then
  git ls-files -z "$bc_path" | while IFS= read -r -d '' tracked_bc; do
    if [ "$root/$tracked_bc" != "$preserved_bc" ]; then
      git rm -f -- "$tracked_bc"
    fi
  done

  find "$bc_path" -type f ! -path "$preserved_bc" -delete
fi
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
    ext=${c_f##*.}

    ########
    # We only look for .c/.cpp files. Check $ext = $f in case the filename is c/cpp.
    ########
    if [ \( "$ext" != "cpp" -a "$ext" != "c" \) -o "$ext" = "$f" ]
    then
        continue
    fi

    filename=$(basename "$c_f")

    # This test requires Windows SDK headers. Preserve its committed bitcode.
    if [ "$td" = "mem_leak" ] && [ "$filename" = "leak_win_heap.c" ]; then
        echo "$0: Skipping '$c_f' (preserving '$preserved_bc')"
        continue
    fi

    ########
    # The output .bc file name.
    ########
    bc_f="$bc_td/$filename.bc"

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
    # Check if this test requires the MSVC ABI target
    ########
    target_arg=""
    case "$filename" in
        msvc_*)
            target_arg="-target x86_64-pc-windows-msvc"
            ;;
    esac

    ########
    # created a .ll, let's make it .bc, as the filename suggests.
    ########
    if test $td == "mem_leak"
    then
        $compiler $target_arg -Wno-everything -S -emit-llvm -fno-discard-value-names -g -I"$root" "$c_f" -o "$bc_f"
    # td = "ae_assert_tests" or "ae_overflow_tests"
    elif test $td == "ae_assert_tests"
    then
        $compiler $target_arg -Wno-everything -S -c -Xclang -DINCLUDEMAIN -Wno-implicit-function-declaration -fno-discard-value-names -g -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    elif test $td == "ae_overflow_tests"
    then
        $compiler $target_arg -Wno-everything -S -c -Xclang -DINCLUDEMAIN -Wno-implicit-function-declaration -fno-discard-value-names -g -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    elif test $td == "ae_recursion_tests"
    then
        $compiler $target_arg -Wno-everything -S -c -Xclang -DINCLUDEMAIN -Wno-implicit-function-declaration -fno-discard-value-names -g -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    elif test $td == "ae_wto_assert"
    then
        $compiler $target_arg -Wno-everything -S -c -Xclang -DINCLUDEMAIN -Wno-implicit-function-declaration -fno-discard-value-names -g -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    else
        $compiler $target_arg -Wno-everything -S -emit-llvm -fno-discard-value-names -I"$root" "$c_f" -o "$bc_f"
    fi
    #llvm-as "$bc_f" -o "$bc_f"
    opt -S -p=mem2reg "$bc_f" -o "$bc_f"
  done
done

fi
