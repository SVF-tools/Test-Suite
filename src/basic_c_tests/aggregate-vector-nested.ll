; extractvalue and extractelement share the nested field path.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %v = insertelement <2 x ptr> poison, ptr @x, i32 1
  %a = insertvalue {i32, <2 x ptr>} poison, <2 x ptr> %v, 1
  %e = extractvalue {i32, <2 x ptr>} %a, 1
  %q = extractelement <2 x ptr> %e, i32 1
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  ret i32 0
}
