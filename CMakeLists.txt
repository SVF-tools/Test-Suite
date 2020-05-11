add_subdirectory(SVF-Tests)
add_executable(
	tester1 basic_c_tests/CI-funptr.c
	tester2 basic_c_tests/CI-global.c
	tester3 basic_c_tests/CI-local.c
	tester4 basic_c_tests/array-constIdx.c
	tester5 basic_c_tests/array-varIdx.c
	tester6 basic_c_tests/array-varIdx2.c
	tester7 basic_c_tests/branch-call.c
	tester8 basic_c_tests/branch-intra.c
	tester9 basic_c_tests/constraint-cycle-copy.c
	tester10 basic_c_tests/constraint-cycle-field.c
	tester11 basic_c_tests/constraint-cycle-pwc.c
	tester12 basic_c_tests/field-ptr-arith-constIdx.c
	tester13 basic_c_tests/field-ptr-arith-varIdx.c
	tester14 basic_c_tests/funptr-global.c
	tester15 basic_c_tests/funptr-nested-call.c
	tester16 basic_c_tests/funptr-simple.c
	tester17 basic_c_tests/funptr-struct.c
	tester18 basic_c_tests/global-array.c
	tester19 basic_c_tests/global-call-noparam.c
	tester20 basic_c_tests/global-call-struct.c
	tester21 basic_c_tests/global-call-twoparms.c
	tester22 basic_c_tests/global-const-struct.c
	tester23 basic_c_tests/global-funptr.c
	tester24 basic_c_tests/global-initializer.c
	tester25 basic_c_tests/global-nested-calls.c
	tester26 basic_c_tests/global-simple.c
	tester27 basic_c_tests/heap-indirect.c
	tester28 basic_c_tests/heap-linkedlist.c
	tester29 basic_c_tests/heap-wrapper.c
	tester30 basic_c_tests/int2pointer.c
	tester31 basic_c_tests/mesa.c
	tester32 basic_c_tests/ptr-dereference1.c
	tester33 basic_c_tests/ptr-dereference2.c
	tester34 basic_c_tests/ptr-dereference3.c
	tester35 basic_c_tests/spec-equake.c
	tester36 basic_c_tests/spec-gap.c
	tester37 basic_c_tests/spec-mesa.c
	tester38 basic_c_tests/spec-parser.c
	tester39 basic_c_tests/spec-vortex.c
	tester40 basic_c_tests/struct-array.c
	tester41 basic_c_tests/struct-assignment-direct.c
	tester42 basic_c_tests/struct-assignment-indirect.c
	tester43 basic_c_tests/struct-assignment-nested.c
	tester44 basic_c_tests/struct-field-multi-dereference.c
	tester45 basic_c_tests/struct-incompab-typecast-nested.c
	tester46 basic_c_tests/struct-incompab-typecast.c
	tester47 basic_c_tests/struct-instance-return.c
	tester48 basic_c_tests/struct-nested-1-layer.c
	tester49 basic_c_tests/struct-nested-2-layers.c
	tester50 basic_c_tests/struct-nested-array1.c
	tester51 basic_c_tests/struct-nested-array2.c
	tester52 basic_c_tests/struct-nested-array3.c
	tester53 basic_c_tests/struct-onefld.c
	tester54 basic_c_tests/struct-simple.c
	tester55 basic_c_tests/struct-twoflds.c
)
add_test(
	Tester tester1 wpa -ander -stat=false
	Tester tester2 wpa -ander -stat=false
	Tester tester3 wpa -ander -stat=false
	Tester tester4 wpa -ander -stat=false
	Tester tester5 wpa -ander -stat=false
	Tester tester6 wpa -ander -stat=false
	Tester tester7 wpa -ander -stat=false
	Tester tester8 wpa -ander -stat=false
	Tester tester9 wpa -ander -stat=false
	Tester tester10 wpa -ander -stat=false
	Tester tester11 wpa -ander -stat=false
	Tester tester12 wpa -ander -stat=false
	Tester tester13 wpa -ander -stat=false
	Tester tester14 wpa -ander -stat=false
	Tester tester15 wpa -ander -stat=false
	Tester tester16 wpa -ander -stat=false
	Tester tester17 wpa -ander -stat=false
	Tester tester18 wpa -ander -stat=false
	Tester tester19 wpa -ander -stat=false
	Tester tester20 wpa -ander -stat=false
	Tester tester20 wpa -ander -stat=false
	Tester tester21 wpa -ander -stat=false
	Tester tester22 wpa -ander -stat=false
	Tester tester23 wpa -ander -stat=false
	Tester tester24 wpa -ander -stat=false
	Tester tester25 wpa -ander -stat=false
	Tester tester26 wpa -ander -stat=false
	Tester tester27 wpa -ander -stat=false
	Tester tester28 wpa -ander -stat=false
	Tester tester29 wpa -ander -stat=false
	Tester tester30 wpa -ander -stat=false
	Tester tester31 wpa -ander -stat=false
	Tester tester32 wpa -ander -stat=false
	Tester tester33 wpa -ander -stat=false
	Tester tester34 wpa -ander -stat=false
	Tester tester35 wpa -ander -stat=false
	Tester tester36 wpa -ander -stat=false
	Tester tester37 wpa -ander -stat=false
	Tester tester38 wpa -ander -stat=false
	Tester tester39 wpa -ander -stat=false
	Tester tester40 wpa -ander -stat=false
	Tester tester41 wpa -ander -stat=false
	Tester tester42 wpa -ander -stat=false
	Tester tester43 wpa -ander -stat=false
	Tester tester44 wpa -ander -stat=false
	Tester tester45 wpa -ander -stat=false
	Tester tester46 wpa -ander -stat=false
	Tester tester47 wpa -ander -stat=false
	Tester tester48 wpa -ander -stat=false
	Tester tester49 wpa -ander -stat=false
	Tester tester50 wpa -ander -stat=false
	Tester tester51 wpa -ander -stat=false
	Tester tester52 wpa -ander -stat=false
	Tester tester53 wpa -ander -stat=false
	Tester tester54 wpa -ander -stat=false
	Tester tester55 wpa -ander -stat=false
)