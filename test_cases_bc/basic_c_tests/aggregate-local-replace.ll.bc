; Replacing a subaggregate replaces its demanded pointer field.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %inner = insertvalue {ptr, ptr} poison, ptr @x, 1
  %old = insertvalue {i32, {ptr, ptr}} poison, ptr @y, 1, 1
  %outer = insertvalue {i32, {ptr, ptr}} %old, {ptr, ptr} %inner, 1
  %q = extractvalue {i32, {ptr, ptr}} %outer, 1, 1
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  ret i32 0
}
