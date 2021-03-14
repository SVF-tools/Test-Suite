if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Basic C tests (basic_c_tests/)
add_test(
  NAME basic_c_tests/CI-funptr.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/CI-funptr.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/CI-global.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/CI-global.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/CI-local.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/CI-local.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/array-constIdx.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/array-constIdx.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/array-varIdx.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/array-varIdx.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/array-varIdx2.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/array-varIdx2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/branch-call.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/branch-call.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/branch-intra.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/branch-intra.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/constraint-cycle-copy.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/constraint-cycle-copy.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/constraint-cycle-field.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/constraint-cycle-field.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/constraint-cycle-pwc.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/constraint-cycle-pwc.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/field-ptr-arith-constIdx.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/field-ptr-arith-constIdx.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/field-ptr-arith-varIdx.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/field-ptr-arith-varIdx.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/funptr-global.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/funptr-global.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/funptr-nested-call.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/funptr-nested-call.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/funptr-simple.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/funptr-simple.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/funptr-struct.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/funptr-struct.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-array.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-array.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-call-noparam.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-call-noparam.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-call-struct.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-call-struct.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-call-twoparms.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-call-twoparms.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-const-struct.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-const-struct.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-funptr.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-funptr.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-initializer.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-initializer.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-nested-calls.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-nested-calls.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/global-simple.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/global-simple.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/heap-indirect.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/heap-indirect.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/heap-linkedlist.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/heap-linkedlist.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/heap-wrapper.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/heap-wrapper.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/int2pointer.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/int2pointer.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/mesa.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/mesa.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/ptr-dereference1.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/ptr-dereference1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/ptr-dereference2.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/ptr-dereference2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/ptr-dereference3.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/ptr-dereference3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/spec-equake.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/spec-equake.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/spec-gap.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/spec-gap.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/spec-mesa.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/spec-mesa.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/spec-parser.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/spec-parser.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/spec-vortex.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/spec-vortex.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-array.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-array.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-assignment-direct.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-assignment-direct.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-assignment-indirect.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-assignment-indirect.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-assignment-nested.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-assignment-nested.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-field-multi-dereference.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-field-multi-dereference.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-incompab-typecast-nested.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-incompab-typecast-nested.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-incompab-typecast.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-incompab-typecast.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-instance-return.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-instance-return.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-nested-1-layer.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-nested-1-layer.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-nested-2-layers.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-nested-2-layers.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-nested-array1.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-nested-array1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-nested-array2.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-nested-array2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-nested-array3.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-nested-array3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-onefld.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-onefld.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME basic_c_tests/struct-simple.c
  COMMAND wpa -ander -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-simple.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
# This test relies on first-fields not being treated as the base.
add_test(
  NAME basic_c_tests/struct-twoflds.c
  COMMAND wpa -ander -stat=false -ff-eq-base=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/basic_c_tests/struct-twoflds.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)

# Flow-sensitive tests (fs_tests/)
add_test(
  NAME fs_tests/array_alias_1.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/array_alias_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/array_alias_2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/array_alias_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/array_alias_3.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/array_alias_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/array_alias_4.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/array_alias_4.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/array_alias_5.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/array_alias_5.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/branch_1.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/branch_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/branch_2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/branch_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/branch_3.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/branch_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/function_pointer.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/function_pointer.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/function_pointer_2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/function_pointer_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/global_1.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/global_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/global_2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/global_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/global_3.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/global_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/global_4.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/global_4.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/global_5.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/global_5.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/pcycle1.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/pcycle1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/pcycle2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/pcycle2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/return.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/return.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/simple_1.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/simple_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/simple_2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/simple_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/simple_3.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/simple_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/strong_update.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/strong_update.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/struct_1.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/struct_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/struct_2.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/struct_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/test-su.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/test-su.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME fs_tests/tt.c
  COMMAND wpa -fspta -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fs_tests/tt.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)

# Versioned flow-sensitive tests.
# It should produce the same results as FSPTA, so we can reuse those tests.
add_test(
  NAME vfs_tests/array_alias_1.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/array_alias_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/array_alias_2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/array_alias_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/array_alias_3.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/array_alias_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/array_alias_4.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/array_alias_4.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/array_alias_5.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/array_alias_5.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/branch_1.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/branch_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/branch_2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/branch_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/branch_3.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/branch_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/function_pointer.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/function_pointer.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/function_pointer_2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/function_pointer_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/global_1.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/global_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/global_2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/global_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/global_3.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/global_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/global_4.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/global_4.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/global_5.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/global_5.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/pcycle1.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/pcycle1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/pcycle2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/pcycle2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/return.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/return.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/simple_1.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/simple_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/simple_2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/simple_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/simple_3.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/simple_3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/strong_update.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/strong_update.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/struct_1.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/struct_1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/struct_2.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/struct_2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/test-su.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/test-su.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME vfs_tests/tt.c
  COMMAND wpa -vfspta -opt-svfg=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/vfs_tests/tt.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)

# Context-sensitive tests (cs_tests/)
add_test(
  NAME cs_tests/cs0.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs0.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs1.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs1.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs10.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs10.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs11.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs11.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs12.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs12.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs13.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs13.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs14.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs14.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs15.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs15.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs16.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs16.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs17.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs17.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs18.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs18.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs19.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs19.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs2.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs20.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs20.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs21.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs21.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs3.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs4.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs4.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs5.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs5.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs6.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs6.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs7.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs7.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs8.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs8.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/cs9.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/cs9.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/funcpoiner.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/funcpoiner.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur0.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur0.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur10.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur10.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur2.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur2.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur3.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur3.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur4.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur4.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur5.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur5.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur6.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur6.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur7.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur7.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur8.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur8.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)
add_test(
  NAME cs_tests/recur9.c
  COMMAND dvf -cxt -print-pts=false -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/cs_tests/recur9.c.bc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
)

# Flow-sensitive type-based heap cloning tests
# Ignore if $SVF_CTIR is not defined.
if (DEFINED ENV{SVF_CTIR})
# (fstbhc_tests/)
    add_test(
      NAME fstbhc_tests/array1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/array1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/basic1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/basic1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/constructor1.cpp
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/constructor1.cpp.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/field1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/field1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/field2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/field2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/field3.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/field3.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/loop.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/loop.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/union.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/union.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/static_first_field.cpp
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/static_first_field.cpp.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/virtual1.cpp
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/virtual1.cpp.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/virtual2.cpp
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/virtual2.cpp.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/virtual3.cpp
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/virtual3.cpp.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/xmalloc1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/xmalloc1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/xmalloc2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/xmalloc2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/xmalloc3.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/xmalloc3.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )

# (fstbhc/fs_tests/)
    add_test(
      NAME fstbhc_tests/fs_tests/array_alias_1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/array_alias_1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/array_alias_2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/array_alias_2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/array_alias_3.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/array_alias_3.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/array_alias_4.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/array_alias_4.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/array_alias_5.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/array_alias_5.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/branch_1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/branch_1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/branch_2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/branch_2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/branch_3.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/branch_3.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/function_pointer.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/function_pointer.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/function_pointer_2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/function_pointer_2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/global_1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/global_1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/global_2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/global_2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/global_3.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/global_3.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/global_4.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/global_4.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/global_5.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/global_5.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/pcycle1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/pcycle1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/simple_1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/simple_1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/simple_2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/simple_2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/simple_3.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/simple_3.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/strong_update.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/strong_update.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/struct_1.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/struct_1.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
    add_test(
      NAME fstbhc_tests/fs_tests/struct_2.c
      COMMAND wpa -fstbhc -stat=false ${CMAKE_CURRENT_SOURCE_DIR}/test_cases_bc/fstbhc_tests/fs_tests/struct_2.c.bc
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}-build/bin
    )
endif()
