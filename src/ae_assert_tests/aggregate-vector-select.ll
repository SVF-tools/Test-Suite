; Preserve the Select condition for a demanded fixed-vector lane.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global i32 7
@y = global i32 9
declare void @svf_assert(i1)

define i32 @main(i32 %argc, ptr %argv) {
  %a = select i1 false, <2 x ptr> <ptr @x, ptr @y>, <2 x ptr> <ptr @y, ptr @x>
  %q = extractelement <2 x ptr> %a, i32 0
  %v = load i32, ptr %q
  %ok = icmp eq i32 %v, 9
  call void @svf_assert(i1 %ok)
  ret i32 0
}
