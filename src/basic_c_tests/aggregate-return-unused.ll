; Calls with unused results still match the callee synthetic output parameters.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null

declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define {ptr} @make() {
  ret {ptr} {ptr @x}
}

define i32 @main() {
  %unused = call {ptr} @make()
  %a = call {ptr} @make()
  %q = extractvalue {ptr} %a, 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @NOALIAS(ptr %q, ptr @y)
  ret i32 0
}
