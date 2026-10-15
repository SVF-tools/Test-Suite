; Both incoming pointer fields reach an aggregate Phi; an unrelated object does not.
; Hand-written IR keeps the aggregate/vector operations independent of the C ABI.

@x = global ptr null
@y = global ptr null
@z = global ptr null
declare void @MAYALIAS(ptr, ptr)
declare void @NOALIAS(ptr, ptr)
@left_pointer = global ptr @x
@right_pointer = global ptr @y

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %cond = icmp eq i32 %argc, 0
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
  %aggregate = phi {ptr} [%la, %left], [%ra, %right]
  %q = extractvalue {ptr} %aggregate, 0
  call void @MAYALIAS(ptr %q, ptr @x)
  call void @MAYALIAS(ptr %q, ptr @y)
  call void @NOALIAS(ptr %q, ptr @z)
  ret i32 0
}
