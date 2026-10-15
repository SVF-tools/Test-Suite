; A dynamic aggregate Select includes both possible fields, without unrelated objects.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define i32 @main(i32 %argc, ptr %argv) {
  %cond = icmp eq i32 %argc, 0
  %aggregate = select i1 %cond, {ptr} {ptr @x}, {ptr} {ptr @y}
  %q = extractvalue {ptr} %aggregate, 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @MAYALIAS(ptr %q, ptr @y)
  call void @NOALIAS(ptr %q, ptr @z)
  ret i32 0
}
