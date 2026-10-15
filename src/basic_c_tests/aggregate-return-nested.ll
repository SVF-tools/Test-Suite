; Direct aggregate returns preserve distinct nested pointer fields.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null

declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)

define {i32, {ptr, [2 x ptr]}} @make() {
  ret {i32, {ptr, [2 x ptr]}} {i32 1, {ptr, [2 x ptr]} {ptr @x, [2 x ptr] [ptr @z, ptr @y]}}
}

define i32 @main() {
  %a = call {i32, {ptr, [2 x ptr]}} @make()
  %q = extractvalue {i32, {ptr, [2 x ptr]}} %a, 1, 0
  %r = extractvalue {i32, {ptr, [2 x ptr]}} %a, 1, 1, 1
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @MAYALIAS(ptr %r, ptr @y)
  call void @NOALIAS(ptr %q, ptr %r)
  ret i32 0
}
