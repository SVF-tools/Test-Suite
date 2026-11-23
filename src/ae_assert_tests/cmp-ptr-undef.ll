@object = global i32 0

declare void @svf_assert_eq(i1, i32)

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %cmp = icmp ne ptr undef, @object
  ; Join the two integer constants to form the expected interval [0, 1].
  %unknown = icmp eq i32 %argc, 1
  %expected = select i1 %unknown, i32 1, i32 0
  call void @svf_assert_eq(i1 %cmp, i32 %expected)
  ret i32 0
}
