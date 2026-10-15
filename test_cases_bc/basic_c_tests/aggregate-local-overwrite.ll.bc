; Nested extractvalue paths retain the last insertion and exclude sibling fields.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %a = insertvalue {i32, {ptr, ptr}} poison, ptr @y, 1, 0
  %b = insertvalue {i32, {ptr, ptr}} %a, ptr @x, 1, 0
  %c = insertvalue {i32, {ptr, ptr}} %b, ptr @z, 1, 1
  %inner = extractvalue {i32, {ptr, ptr}} %c, 1
  %q = extractvalue {ptr, ptr} %inner, 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  call void @NOALIAS(ptr %q, ptr @z)
  ret i32 0
}
