# Allocation-size diagnostic tests

The `AllocationSize_*.c` cases in `src/ae_overflow_tests` follow the existing
small C tests and use `SAFE_BUFACCESS` / `UNSAFE_BUFACCESS` checkpoints. The
matching LLVM IR files in `test_cases_bc/ae_overflow_tests` are generated with
the same compiler flags and `mem2reg` pass as `generate_bc.sh`.

The checkpoints validate detection behavior. In addition,
`check_allocation_bounds.py` checks the allocation intervals printed by AE:

```c
// EXPECT-ALLOC-SIZE: [1, 10]
```

Each comment expects one diagnostic with that allocation interval. Multiple
comments are allowed; the checker compares counts without depending on report
order. It rejects unexpected or missing diagnostics and nonzero AE exit codes.
Use `// EXPECT-NO-OVERFLOW` for cases that should produce no overflow report.

The CMake registration runs these checks in all six existing overflow test
configurations: dense, semi-sparse, and sparse, with and without recursive
widening/narrowing. All use `-field-limit=1024`.

From an SVF build configured with this repository at `SVF/Test-Suite`, run:

```sh
ctest -R AllocationSize_ --output-on-failure
```

The cases cover constant char/int arrays, variable-length char arrays, malloc,
calloc with one or two variable factors, zero lower bounds, unknown sizes,
upper/both-bound truncation, memcpy/memset/strcpy/strcat, interior pointers, and
accesses below, between, or at the allocation bounds. The between-bounds case
explicitly preserves AE's existing upper-bound detection behavior; it does not
claim that the access is safe for every concrete allocation.

`AllocationSize_vla_int.c` records an existing byte-size bug: dynamic `int`
allocas omit the element byte size, whereas constant arrays account for it.
The correct expected interval is `[4, 40]` on the supported targets. Its
`KNOWN-ALLOC-SIZE: [1, 10]` comment permits only that exact known result to
return code 77, which CTest marks skipped. Crashes and other mismatches still
fail; once the bug is fixed, the correct result passes automatically. This is
separate from SVF PR #1929, which carries lower bounds into reports without
changing the allocation upper-bound calculation or overflow detection.

These integration cases do not force every internal abstract state. Empty
size vectors, bottom/negative size factors, and machine-integer multiplication
overflow need dedicated helper-level tests rather than C cases with undefined
or platform-dependent allocation behavior.
