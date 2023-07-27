# wpa tests (ctest -R wpa_tests -VV)
# folder and commands list act in parallel. e.g. for index 0 command "wpa -ander -stat=false" will be run on basic_c_tests folder.
list(
  APPEND
  wpa_folders
  basic_c_tests
  basic_cpp_tests
  fs_tests
  vfs_tests
)

list(
  APPEND
  commands
  "wpa -ander"
  "wpa -ander"
  "wpa -fspta"
  "wpa -vfspta"
)

list(LENGTH wpa_folders wpa_len1)
math(EXPR wpa_len2 "${wpa_len1} - 1")

# loops over each command in commands list
foreach(i RANGE ${wpa_len2})
  # gets the command and folder of index i
  list(GET wpa_folders ${i} folder)
  list(GET commands ${i} cmd)
  # creates a list of each file in folder
  file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  string(REPLACE " " ";" commandtemp ${cmd})
  set(command ${commandtemp})
  # loops over each file creating a test
  foreach(filename ${files})
    if (${filename} MATCHES ".pre.bc" OR ${filename} MATCHES ".pre.svf.bc" OR ${filename} MATCHES ".svf.bc")
      continue()
    endif()
    add_test(
      NAME wpa_tests/${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
  endforeach()
endforeach()


# dvf and mta tests (ctest -R dvf_tests -VV)
list(
  APPEND
  dvf_folders
  fs_tests
  cs_tests
  mta
)

list(
  APPEND
  dvf_commands
  "dvf -dfs -print-pts=false"
  "dvf -cxt -print-pts=false"
  "mta -mhp-validation -lock-validation"
)

list(LENGTH dvf_folders dvf_len1)
math(EXPR dvf_len2 "${dvf_len1} - 1")

# loops over each command in commands list
foreach(i RANGE ${dvf_len2})
  # gets the command and folder of index i
  list(GET dvf_folders ${i} folder)
  list(GET dvf_commands ${i} cmd)
  # creates a list of each file in folder
  file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  string(REPLACE " " ";" commandtemp ${cmd})
  set(command ${commandtemp})
  # loops over each file creating a test
  foreach(filename ${files})
    if (${filename} MATCHES ".pre.bc" OR ${filename} MATCHES ".pre.svf.bc" OR ${filename} MATCHES ".svf.bc")
      continue()
    endif()
    add_test(
      NAME dvf_tests/${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
  endforeach()
endforeach()


# differential_tests fspta-vfspta  (ctest -R diff_tests-fs -VV)
file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/*.bc*")
foreach(filename ${files})
  add_test(
    NAME diff_tests-fs/fspta-vfspta/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/difftest.py
      "wpa -fspta -opt-svfg=false"
      "wpa -vfspta -opt-svfg=false"
      ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
endforeach()


# differential_tests anderson (ctest -R diff_tests-ander -VV) and (ctest -R diff_tests-wr-ander -VV) and (ctest -R diff_tests-wr-svfg -VV)
list(
  APPEND
  diff_tests_anderson_folders
  basic_c_tests
  basic_cpp_tests
  complex_tests
  fs_tests
)
foreach(folder ${diff_tests_anderson_folders})
  file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  foreach(filename ${files})
    if (${filename} MATCHES ".pre.bc" OR ${filename} MATCHES ".pre.svf.bc" OR ${filename} MATCHES ".svf.bc")
      continue()
    endif()

    add_test(
      NAME diff_tests-ander/ander-nander/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/difftest.py
        "wpa -ander -alias-check=false"
        "wpa -nander -alias-check=false"
        ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    # read and write ander
    # change file extension to .pre.bc
    string(REGEX REPLACE "[.]bc$" ".pre.svf.bc" readFile ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
    add_test(
      NAME diff_tests-wr-ander/ander-read-write/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/difftest.py
        "svf-ex -ander -alias-check=false -write-ander=ir_annotator"
        "svf-ex -ander -alias-check=false -read-ander=ir_annotator"
        ${CMAKE_CURRENT_SOURCE_DIR}/${filename} ${readFile}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

  endforeach()
endforeach()

# differential_tests read_write_svfg with crux-bc (ctest -R diff_tests-wr-svfg-cruxbc -VV)
list(
  APPEND
  diff_tests_cruxbc
  bc
  dc
  xxd
  libbz2.so
  bzip2recover
)
foreach(file ${diff_tests_cruxbc})
  file(GLOB filename RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/crux-bc/${file}.bc")
  add_test(
    NAME diff_tests-wr-svfg-cruxbc/read_write_svfg_crux/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/difftest.py
      "wpa -ander -svfg -alias-check=false -write-svfg=read_write_file"
      "wpa -ander -svfg -alias-check=false -read-svfg=read_write_file"
      ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
endforeach()

# saber mem_leak tests  (ctest -R mem_leak -VV)
set(cmd "saber -leak -valid-tests -stat=false")
file(GLOB mem_leak_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/mem_leak/*.bc*")
string(REPLACE " " ";" commandtemp ${cmd})
set(command ${commandtemp})
# loops over each file creating a test
foreach(filename ${mem_leak_files})
  add_test(
      NAME mem_leak/${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
endforeach()

# saber double_free tests (ctest -R double_free -VV)
set(cmd "saber -dfree -valid-tests -stat=false")
file(GLOB doublefree_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/double_free/*.bc*")
string(REPLACE " " ";" commandtemp ${cmd})
set(command ${commandtemp})
# loops over each file creating a test
foreach(filename ${doublefree_files})
  add_test(
          NAME double_free/${filename}
          COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
endforeach()

# cfl tests (ctest -R cfl_tests -VV)
list(
  APPEND
  cfl_test_bc_folders
  basic_c_tests
  basic_cpp_tests
)
foreach(folder ${cfl_test_bc_folders})
  set(POCRcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/svf/include/CFL/grammar/PAGGrammar.txt -stat=false -pocr-alias")
  if(${folder} STREQUAL basic_c_tests )
    set(HYBRIDcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/svf/include/CFL/grammar/PAGGrammar.txt -stat=false -pocr-hybrid")
    set(PEGcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/svf/include/CFL/grammar/PEGGrammar.txt -peg-transfer -stat=false")
    set(VFGcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/svf/include/CFL/grammar/VFGGrammar.txt -cflsvfg -stat=false")
    set(cmd "cfl -grammar=${PROJECT_SOURCE_DIR}/svf/include/CFL/grammar/PAGGrammar.txt -stat=false")
    string(REPLACE " " ";" HYBRIDcommandtemp ${HYBRIDcmd})
    string(REPLACE " " ";" PEGcommandtemp ${PEGcmd})
    string(REPLACE " " ";" VFGcommandtemp ${VFGcmd})
    string(REPLACE " " ";" commandtemp ${cmd})
    set(HYBRIDcommand ${HYBRIDcommandtemp})
    set(PEGcommand ${PEGcommandtemp})
    set(VFGcommand ${VFGcommandtemp})
    set(command ${commandtemp})
  endif()
  file(GLOB cfl_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  string(REPLACE " " ";" POCRcommandtemp ${POCRcmd})
  set(POCRcommand ${POCRcommandtemp})
  # loops over each file creating a test
  foreach(filename ${cfl_files})
  add_test(
    NAME cfl_tests/${filename}POCR
    COMMAND ${POCRcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
  if(${folder} STREQUAL basic_c_tests )
    add_test(
      NAME cfl_tests/${filename}HYBRID
      COMMAND ${HYBRIDcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    add_test(
      NAME cfl_tests/${filename}PEG
      COMMAND ${PEGcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    add_test(
      NAME cfl_tests/${filename}VFG
      COMMAND ${VFGcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    add_test(
      NAME cfl_tests/${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
  endif()
  endforeach()
endforeach()

# Crux bc Small: Filesystem & Performance regression testing
# Run with: (ctest -R diff-perf-cruxbc-small -VV)
set(diff_tests_cruxbc_small
  dc bc libbz2.so bunzip2 htop)
foreach(file ${diff_tests_cruxbc_small})
  file(GLOB filename RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/crux-bc/${file}.bc")
  add_test(
    NAME diff-perf-cruxbc-small/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/difftest.py
      "wpa -vfspta -dump-vfg -dump-json=ir.json"
      "wpa -vfspta -read-json"
      ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      "ir.json"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
endforeach()

# Crux bc Big: Filesystem & Performance regression testing
# Run with (ctest -R diff-perf-cruxbc-big -VV)
set(diff_tests_cruxbc_big libcurl.so bash)
foreach(file ${diff_tests_cruxbc_big})
  file(GLOB filename RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/crux-bc/${file}.bc")
  add_test(
    NAME diff-perf-cruxbc-big/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/difftest.py
      "wpa -ander -dump-json=ir.json"
      "wpa -ander -read-json"
      ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      "ir.json"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
endforeach()
