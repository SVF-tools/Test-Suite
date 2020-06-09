#!/bin/sh
# Generates the add_test(...) required by CMake given a
# directory with tests and the command (minus the actual
# target .bc).

if [ $# -ne 2 ]; then
  echo "usage: $0 dir command"
  exit 1
fi

dir="$1"
# Strip trailing '/' so we don't double up.
dir=`echo "$dir" | sed 's/\/$//'`
cmd="$2"

root=$(cd "$(dirname "$0")"; pwd)
cd $root
bc_dir_name="test_cases_bc"

for f in "$dir/"*; do
  # Ignore non-.c/.cpp files.
  ext=${f##*.}
  if [ \( "$ext" != "c" -a "$ext" != "cpp" \) -o "$ext" = "$f" ]; then
    continue;
  fi

  echo "add_test("
  echo "  NAME $f"
  echo "  COMMAND $cmd \${CMAKE_CURRENT_SOURCE_DIR}/$bc_dir_name/$f.bc"
  echo "  WORKING_DIRECTORY \${PROJECT_SOURCE_DIR}/\${CMAKE_BUILD_TYPE}-build/bin"
  echo ")"
done
