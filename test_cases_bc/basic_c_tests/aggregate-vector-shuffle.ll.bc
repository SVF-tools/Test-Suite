; The shuffle mask selects a lane from the second operand.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %v = shufflevector <2 x ptr> <ptr @y, ptr @z>, <2 x ptr> <ptr @x, ptr @y>, <2 x i32> <i32 2, i32 0>
  %q = extractelement <2 x ptr> %v, i32 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  call void @NOALIAS(ptr %q, ptr @z)
  ret i32 0
}
