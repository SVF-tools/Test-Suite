; A pointer inside a constant array of structs is resolved by its full field path.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %q = extractvalue [2 x {ptr}] [{ptr} {ptr @y}, {ptr} {ptr @x}], 1, 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  ret i32 0
}
