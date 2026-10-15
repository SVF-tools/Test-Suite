; Preserve the predecessor of each aggregate Phi field.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global i32 7
@y = global i32 9
declare void @svf_assert(i1)
@left_pointer = global ptr @x
@right_pointer = global ptr @y

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %control = load i32, ptr @x
  %cond = icmp eq i32 %control, 7
  br i1 %cond, label %left, label %right
left:
  %lp = load ptr, ptr @left_pointer
  %la = insertvalue {ptr} poison, ptr %lp, 0
  br label %join
right:
  %rp = load ptr, ptr @right_pointer
  %ra = insertvalue {ptr} poison, ptr %rp, 0
  br label %join
join:
  %a = phi {ptr} [%la, %left], [%ra, %right]
  %q = extractvalue {ptr} %a, 0
  %v = load i32, ptr %q
  %ok = icmp eq i32 %v, 7
  call void @svf_assert(i1 %ok)
  ret i32 0
}
