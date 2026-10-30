; Regression: Store source merged with the written object into a Copy SCC.
;
; %value = *@box and *%mixed = %value create opposite Copy edges between
; %value and the @box object, so Andersen merges them into one SCC. After
; %mixed also points to @other, the Store source is rewritten to the merged
; representative. processStore() must not reject the retargeted edge by the
; representative's PAG type.
;
; Expected: %p = *@other sees @target, because the Store must write the box
; object into @other. The Store must still contribute its target after SCC merging.
; Reproduce the Andersen miss with -ff-eq-base=true; with the default object
; layout this particular shape does not reach the failing path.

@target = global i8 0
@box = global [1 x ptr] [ptr @target]
@other = global ptr null
@holder = global ptr @other

define i32 @main(i32 %argc, ptr %argv) {
entry:
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
