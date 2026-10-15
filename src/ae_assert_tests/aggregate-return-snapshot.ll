; A delayed extraction reads the first call snapshot after a second call completes.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global i32 7
@y = global i32 11
declare void @svf_assert(i1)
define {ptr} @identity(ptr %p) {
  %a = insertvalue {ptr} poison, ptr %p, 0
  ret {ptr} %a
}

define i32 @main(i32 %argc, ptr %argv) {
  %a = call {ptr} @identity(ptr @x)
  %b = call {ptr} @identity(ptr @y)
  %q = extractvalue {ptr} %a, 0
  %v = load i32, ptr %q
  %ok = icmp eq i32 %v, 7
  call void @svf_assert(i1 %ok)
  ret i32 0
}
