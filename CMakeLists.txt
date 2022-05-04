if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# folder and commands list act in parallel. e.g. for index 0 command "wpa -ander -stat=false" will be run on basic_c_tests folder.
list(
  APPEND
  folders
  basic_c_tests
  basic_cpp_tests
  fs_tests
  vfs_tests
  cs_tests
  fstbhc_tests
  fstbhc_tests/fs_tests
  mta
)

list(
  APPEND
  commands
  "wpa -ander -stat=false"
  "wpa -ander -stat=false"
  "wpa -fspta -stat=false"
  "wpa -vfspta -opt-svfg=false -stat=false"
  "dvf -cxt -print-pts=false -stat=false"
  "wpa -fstbhc -stat=false"
  "wpa -fstbhc -stat=false"
  "mta -mhp-validation -lock-validation -stat=false"
)

list(LENGTH folders len1)
math(EXPR len2 "${len1} - 1")

# loops over each command in commands list
foreach(i RANGE ${len2})
  # gets the command and folder of index i
  list(GET folders ${i} folder)
  list(GET commands ${i} cmd)
  # creates a list of each file in folder
  file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  string(REPLACE " " ";" commandtemp ${cmd})
  set(command ${commandtemp})
  # loops over each file creating a test
  foreach(filename ${files})
    if (${filename} MATCHES "struct-twoflds.c.bc")
      continue()
    endif()
    if (${filename} MATCHES ".pre.bc" OR ${filename} MATCHES ".pre.svf.bc" OR ${filename} MATCHES ".svf.bc")
      continue()
    endif()
    add_test(
      NAME points-to/${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
  endforeach()
endforeach()

add_test(
  NAME points-to/basic_c_tests/struct-twoflds.c
  COMMAND wpa -ander -stat=false -ff-eq-base=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-twoflds.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)

# differential_tests fspta-vfspta
file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/*.bc*")
foreach(filename ${files})
  add_test(
    NAME diff_tests/fspta-vfspta/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -fspta -opt-svfg=false" "wpa -vfspta -opt-svfg=false" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
  set_tests_properties(diff_tests/fspta-vfspta/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")
endforeach()


# differential_tests anderson
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
    if (${filename} MATCHES "struct-twoflds.c.bc")
      continue()
    endif()
    if (${filename} MATCHES ".pre.bc" OR ${filename} MATCHES ".pre.svf.bc" OR ${filename} MATCHES ".svf.bc")
      continue()
    endif()

    add_test(
      NAME diff_tests/ander-nander/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -ander -alias-check=false" "wpa -nander -alias-check=false" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    set_tests_properties(diff_tests/ander-nander/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")

    # read and write svfg
    add_test(
      NAME diff_tests/svfg-read-write/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -ander -svfg -alias-check=false -write-svfg=read_write_file" "wpa -ander -svfg -alias-check=false -read-svfg=read_write_file" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    set_tests_properties(diff_tests/svfg-read-write/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")

    # read and write ander
    # change file extension to .pre.bc
    string(REGEX REPLACE "[.]bc$" ".pre.svf.bc" readFile ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
    add_test(
      NAME diff_tests/ander-read-write/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "svf-ex -ander -alias-check=false -write-ander=ir_annotator" "svf-ex -ander -alias-check=false -read-ander=ir_annotator" ${CMAKE_CURRENT_SOURCE_DIR}/${filename} ${readFile}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    set_tests_properties(diff_tests/ander-read-write/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")

  endforeach()
endforeach()

add_test(
      NAME diff_tests/ander-nander/basic_c_tests/struct-twoflds.c.bc
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -ander -ff-eq-base=false -alias-check=false" "wpa -nander -ff-eq-base=false -alias-check=false" ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-twoflds.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
set_tests_properties(diff_tests/ander-nander/basic_c_tests/struct-twoflds.c.bc PROPERTIES PASS_REGULAR_EXPRESSION "0")

add_test(
      NAME diff_tests/svfg-read-write/basic_c_tests/struct-twoflds.c.bc
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -fspta -alias-check=false -write-svfg=read_write_file" "wpa -fspta -alias-check=false -read-svfg=read_write_file" ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-twoflds.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
set_tests_properties(diff_tests/svfg-read-write/basic_c_tests/struct-twoflds.c.bc PROPERTIES PASS_REGULAR_EXPRESSION "0")

# differential_tests read_write_svfg with crux-bc
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
    NAME diff_tests/read_write_svfg_crux/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/diff_tests/diff_tests.sh "wpa -ander -svfg -alias-check=false -write-svfg=read_write_file" "wpa -ander -svfg -alias-check=false -read-svfg=read_write_file" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
  )
  set_tests_properties(diff_tests/read_write_svfg_crux/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")
endforeach()

# saber mem_leak tests
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
