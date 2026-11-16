These cases require SVF's AE-only `-ae-entry=<name>` option. Generate their
fixtures with `generate_bc.sh`, then run `ctest -R '^ae_entry/' --output-on-failure`
from the SVF build directory.

The cases cover unknown entry arguments despite a known caller, a custom root
inside a recursive SCC, global initialization and overwrites, exact symbols
with numeric suffixes, file-qualified static functions, ambiguity (including
locations or missing debug info), declaration-only names, and invalid requests.
Each successful
analysis case runs in dense, semi-sparse and full-sparse modes.

The checker validates diagnostics as well as exit codes: global-value tests
must print two successful assertion verifications and no assertion failure.
This remains effective in Release builds where C/C++ assertions are disabled.
Full-sparse custom-entry runs use AE's conservative dense-memory fallback.

`static.c` keeps both static functions through calls from main. The second uses
the asm symbol `foo.1` and a `#line` directive giving it `/x/src/b.c`, while the
first is `foo` at `/x/src/a.c:1`. `generate_bc.sh` compiles it with LLVM 22
`clang -S -emit-llvm -fno-discard-value-names -g`, then `opt -S -p=mem2reg`.
It also generates `static_no_debug.c.bc` without `-g`. No linking is needed.
The suffix fixture checks removing exactly one trailing numeric suffix and
preserving nonnumeric suffixes. Qualifier errors check path component boundaries
and splitting on the last colon. All previous non-entry tests remain unchanged.
