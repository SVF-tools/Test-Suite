if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

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
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
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
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
  endforeach()
endforeach()


# differential_tests fspta-vfspta  (ctest -R diff_tests-fs -VV)
file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/*.bc*")
foreach(filename ${files})
  add_test(
    NAME diff_tests-fs/fspta-vfspta/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -fspta -opt-svfg=false" "wpa -vfspta -opt-svfg=false" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
  set_tests_properties(diff_tests-fs/fspta-vfspta/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")
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
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -ander -alias-check=false" "wpa -nander -alias-check=false" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    set_tests_properties(diff_tests-ander/ander-nander/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")

    # read and write ander
    # change file extension to .pre.bc
    string(REGEX REPLACE "[.]bc$" ".pre.svf.bc" readFile ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
    add_test(
      NAME diff_tests-wr-ander/ander-read-write/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "svf-ex -ander -alias-check=false -write-ander=ir_annotator" "svf-ex -ander -alias-check=false -read-ander=ir_annotator" ${CMAKE_CURRENT_SOURCE_DIR}/${filename} ${readFile}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    set_tests_properties(diff_tests-wr-ander/ander-read-write/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")
   
  endforeach()
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
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
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
          WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
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
  set(cmd "cfl -grammar=${PROJECT_SOURCE_DIR}/include/CFL/CFLGrammar.txt -stat=false")
  if(${folder} STREQUAL basic_c_tests )
    set(PEGcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/include/CFL/PEGGrammar.txt -peg-transfer -stat=false")
    set(VFGcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/include/CFL/VFG.txt -cflsvfg -stat=false")
    set(POCRcmd "cfl -grammar=${PROJECT_SOURCE_DIR}/include/CFL/CFLGrammar.txt -stat=false -cfldata")
    string(REPLACE " " ";" PEGcommandtemp ${PEGcmd})
    string(REPLACE " " ";" VFGcommandtemp ${VFGcmd})
    string(REPLACE " " ";" POCRcommandtemp ${POCRcmd})
    set(PEGcommand ${PEGcommandtemp})
    set(VFGcommand ${VFGcommandtemp})
    set(POCRcommand ${POCRcommandtemp})
  endif()
  file(GLOB cfl_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  string(REPLACE " " ";" commandtemp ${cmd})
  set(command ${commandtemp})
  # loops over each file creating a test
  foreach(filename ${cfl_files})
  add_test(
      NAME cfl_tests/${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
  if(${folder} STREQUAL basic_c_tests )
    add_test(
      NAME cfl_tests/${filename}PEG
      COMMAND ${PEGcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME cfl_tests/${filename}VFG
      COMMAND ${VFGcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
      add_test(
      NAME cfl_tests/${filename}POCR
      COMMAND ${POCRcommand} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
  endif()
  endforeach()
endforeach()

# Performance regression testing (ctest -R diff-perf-cruxbc -VV)
list(
  APPEND
  diff_tests_cruxbc
  libcurl.so
  bash
)
set(cmd "wpa -vfspta -dump-vfg")
string(REPLACE " " ";" commandtemp ${cmd})
set(command ${commandtemp})
foreach(file ${diff_tests_cruxbc})
  file(GLOB filename RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/crux-bc/${file}.bc")
  add_test(
    NAME diff-perf-cruxbc/${filename}
    COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
  set_tests_properties(diff-perf-cruxbc/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")
endforeach()
