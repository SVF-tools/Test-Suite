; Preserve the Select condition instead of unioning the two field values.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global i32 7
@y = global i32 9
declare void @svf_assert(i1)

define i32 @main(i32 %argc, ptr %argv) {
  %a = select i1 true, {ptr} {ptr @x}, {ptr} {ptr @y}
  %q = extractvalue {ptr} %a, 0
  %v = load i32, ptr %q
  %ok = icmp eq i32 %v, 7
  call void @svf_assert(i1 %ok)
  ret i32 0
}
