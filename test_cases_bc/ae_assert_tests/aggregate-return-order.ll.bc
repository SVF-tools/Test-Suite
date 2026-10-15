; LLVM block-list order differs from dominance order: snapshot before field use.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global i32 7
declare void @svf_assert(i1)
define {ptr} @make(ptr %p) {
  %a = insertvalue {ptr} poison, ptr %p, 0
  ret {ptr} %a
}
define i32 @main() {
entry:
  br label %produce
use:
  %p = extractvalue {{ptr}, i32} %wrapped, 0, 0
  %v = load i32, ptr %p
  %ok = icmp eq i32 %v, 7
  call void @svf_assert(i1 %ok)
  ret i32 0
produce:
  %a = call {ptr} @make(ptr @x)
  %wrapped = insertvalue {{ptr}, i32} poison, {ptr} %a, 0
  br label %use
}
