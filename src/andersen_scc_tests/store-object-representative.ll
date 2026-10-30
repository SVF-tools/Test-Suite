; Store source rewritten to a non-pointer object representative after Copy SCC
; merging. The inherited Store must still propagate @target to @other, so the
; final Load and @target must alias under the default analysis configuration.

@target = global i8 0
@box = global [1 x ptr] zeroinitializer
@other = global ptr null
@holder = global ptr @other

define i32 @main(i32 %argc, ptr %argv) {
entry:
  store ptr @target, ptr @box
  %choose = icmp eq i32 %argc, 0
  %q = load ptr, ptr @holder
  %mixed = select i1 %choose, ptr @box, ptr %q
  %value = load ptr, ptr @box
  store ptr %value, ptr %mixed
  %p = load ptr, ptr @other
  call void @MAYALIAS(ptr %p, ptr @target)
  ret i32 0
}

; Checked by SVF's built-in alias validator.
define void @MAYALIAS(ptr %left, ptr %right) {
  ret void
}
