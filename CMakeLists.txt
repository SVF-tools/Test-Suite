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
    add_test(
      NAME ${filename}
      COMMAND ${command} ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
  endforeach()
endforeach()

add_test(
  NAME basic_c_tests/struct-twoflds.c
  COMMAND wpa -ander -stat=false -ff-eq-base=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-twoflds.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)

# differential_tests fspta-vfspta
file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/*.bc*")
foreach(filename ${files})
  add_test(
    NAME diff_tests/fspta-vfspta/${filename}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/diff_tests/diff_tests "wpa -fspta -opt-svfg=false" "wpa -vfspta -opt-svfg=false" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
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
)
foreach(folder ${diff_tests_anderson_folders})
  file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/${folder}/*.bc*")
  foreach(filename ${files})
    if (${filename} MATCHES "struct-twoflds.c.bc")
      continue()
    endif()
    add_test(
      NAME diff_tests/ander-nander/${filename}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/diff_tests/diff_tests "wpa -ander" "wpa -nander" ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    set_tests_properties(diff_tests/ander-nander/${filename} PROPERTIES PASS_REGULAR_EXPRESSION "0")
  endforeach()
endforeach()

add_test(
      NAME diff_tests/ander-nander/basic_c_tests/struct-twoflds.c.bc
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/diff_tests/diff_tests "wpa -ander -ff-eq-base=fals" "wpa -nander -ff-eq-base=fals" ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-twoflds.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
set_tests_properties(diff_tests/ander-nander/basic_c_tests/struct-twoflds.c.bc PROPERTIES PASS_REGULAR_EXPRESSION "0")