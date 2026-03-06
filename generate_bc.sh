#!/bin/sh
# Generate bitcode for the .c/.cpp tests.
# Each entry in all_dirs is "src_subpath:bc_subpath".
# - Non-AE tests: src under src/<dir>, bc under test_cases_bc/<dir>
# - AE tests: src under src/ae_pass/<dir> or src/ae_dense_pass/<dir>,
#             bc under ae_pass/<dir> or ae_dense_pass/<dir>

sysOS=$(uname -s)

all_dirs="
  basic_c_tests:test_cases_bc/basic_c_tests
  basic_cpp_tests:test_cases_bc/basic_cpp_tests
  complex_tests:test_cases_bc/complex_tests
  cpp_types:test_cases_bc/cpp_types
  cs_tests:test_cases_bc/cs_tests
  fs_tests:test_cases_bc/fs_tests
  mem_leak:test_cases_bc/mem_leak
  double_free:test_cases_bc/double_free
  mta:test_cases_bc/mta
  non_annotated_tests:test_cases_bc/non_annotated_tests
  path_tests:test_cases_bc/path_tests
  objtype_tests:test_cases_bc/objtype_tests
  ae_pass/ae_assert_tests:ae_pass/ae_assert_tests
  ae_pass/ae_nullptr_deref_tests:ae_pass/ae_nullptr_deref_tests
  ae_pass/ae_overflow_tests:ae_pass/ae_overflow_tests
  ae_pass/ae_recursion_tests:ae_pass/ae_recursion_tests
  ae_dense_pass/ae_assert_tests:ae_dense_pass/ae_assert_tests
  ae_dense_pass/ae_nullptr_deref_tests:ae_dense_pass/ae_nullptr_deref_tests
  ae_dense_pass/ae_overflow_tests:ae_dense_pass/ae_overflow_tests
  ae_dense_pass/ae_recursion_tests:ae_dense_pass/ae_recursion_tests
"

root=$(cd "$(dirname "$0")"; pwd)

if [[ $sysOS == "Linux" ]];then

########
# Remove previous bc folders and create new ones.
########
git rm -rf "$root/test_cases_bc"
git rm -rf "$root/ae_pass" 2>/dev/null || true
git rm -rf "$root/ae_dense_pass" 2>/dev/null || true
mkdir -p "$root/test_cases_bc"

########
# Loops through each entry in all_dirs.
########
for entry in $all_dirs; do
  src_sub="${entry%%:*}"
  bc_sub="${entry##*:}"

  full_td="$root/src/$src_sub"
  bc_td="$root/$bc_sub"

  # Skip if source dir doesn't exist
  [ -d "$full_td" ] || continue

  mkdir -p "$bc_td"

  # Determine if this is an AE test directory
  is_ae=false
  case "$src_sub" in
    ae_pass/*|ae_dense_pass/*) is_ae=true ;;
  esac

  # Extract the leaf directory name for mem_leak check
  leaf="${src_sub##*/}"

  for c_f in "$full_td/"*; do
    ext=${c_f##*.}

    if [ \( "$ext" != "cpp" -a "$ext" != "c" \) -o "$ext" = "$f" ]
    then
        continue
    fi

    bc_f="$bc_td/$(basename "$c_f").bc"

    if [ "$bc_f" -nt "$c_f" ]; then
        continue
    fi

    compiler=""
    if [ "$ext" = "c" ]; then
        compiler="clang"
    else
        compiler="clang++"
    fi

    echo "$0: Compiling '$c_f'"
    echo "$0:        to '$bc_f'"

    if [ "$is_ae" = true ]; then
        $compiler -Wno-everything -S -c -Xclang -DINCLUDEMAIN -Wno-implicit-function-declaration -fno-discard-value-names -g -emit-llvm -I"$root" "$c_f" -o "$bc_f"
    elif test "$leaf" == "mem_leak"; then
        $compiler -Wno-everything -S -emit-llvm -fno-discard-value-names -g -I"$root" "$c_f" -o "$bc_f"
    else
        $compiler -Wno-everything -S -emit-llvm -fno-discard-value-names -I"$root" "$c_f" -o "$bc_f"
    fi
    #llvm-as "$bc_f" -o "$bc_f"
    opt -S -p=mem2reg "$bc_f" -o "$bc_f"
  done
done

fi
