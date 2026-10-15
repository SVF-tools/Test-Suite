; A fixed-vector pointer lane nested inside a returned aggregate retains its value.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global i32 7
@y = global i32 9
declare void @svf_assert(i1)
define {<2 x ptr>, i32} @make(ptr %p, ptr %q) {
  %v0 = insertelement <2 x ptr> poison, ptr %p, i32 0
  %v1 = insertelement <2 x ptr> %v0, ptr %q, i32 1
  %a = insertvalue {<2 x ptr>, i32} poison, <2 x ptr> %v1, 0
  ret {<2 x ptr>, i32} %a
}
define i32 @main() {
  %a = call {<2 x ptr>, i32} @make(ptr @x, ptr @y)
  %vec = extractvalue {<2 x ptr>, i32} %a, 0
  %p = extractelement <2 x ptr> %vec, i32 0
  %v = load i32, ptr %p
  %ok = icmp eq i32 %v, 7
  call void @svf_assert(i1 %ok)
  ret i32 0
}
