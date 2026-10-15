; Demanded return fields propagate through a forwarding function.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null

declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define {ptr} @make() {
  ret {ptr} {ptr @x}
}

define {ptr} @wrap() {
  %a = call {ptr} @make()
  ret {ptr} %a
}

define i32 @main() {
  %a = call {ptr} @wrap()
  %q = extractvalue {ptr} %a, 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  ret i32 0
}
