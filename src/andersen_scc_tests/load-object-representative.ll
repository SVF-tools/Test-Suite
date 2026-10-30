; Regression: Load result merged with the loaded object into a Copy SCC.
;
; %p = *%mixed and *@box = %p create opposite Copy edges between %p and the
; @box object, so Andersen merges them into one SCC. The representative can be
; the non-pointer @box object. processLoad()/processStore() must not reject the
; retargeted edge by the representative's PAG type.
;
; Expected: %p points to @target (it may point to @box or @other; @other holds
; @target). The Load must still contribute its target after SCC merging.

@box = global [1 x ptr] zeroinitializer
@target = global i8 0
@other = global ptr @target
@holder = global ptr @other

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %choose = icmp eq i32 %argc, 0
  %q = load ptr, ptr @holder
  %mixed = select i1 %choose, ptr @box, ptr %q
  %p = load ptr, ptr %mixed
  store ptr %p, ptr @box
  call void @MAYALIAS(ptr %p, ptr @target)
  ret i32 0
}

; Checked by SVF's built-in alias validator.
define void @MAYALIAS(ptr %left, ptr %right) {
  ret void
}
