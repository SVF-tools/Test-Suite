declare void @svf_assert(i1)

define i32 @main() {
entry:
  %cmp = icmp ne i32 0, poison
  %result = select i1 %cmp, i32 1, i32 0
  %in_range = icmp ult i32 %result, 2
  call void @svf_assert(i1 %in_range)
  ret i32 0
}
