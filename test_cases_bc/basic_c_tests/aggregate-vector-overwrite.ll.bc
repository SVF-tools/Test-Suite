; Constant-lane insertelement/extractelement retains the overwrite, not the other lane.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %v0 = insertelement <2 x ptr> poison, ptr @y, i32 0
  %v1 = insertelement <2 x ptr> %v0, ptr @x, i32 0
  %v2 = insertelement <2 x ptr> %v1, ptr @z, i32 1
  %q = extractelement <2 x ptr> %v2, i32 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  call void @NOALIAS(ptr %q, ptr @z)
  ret i32 0
}
