These cases require SVF's AE-only `-ae-entry=<name>` option. Generate their
fixtures with `generate_bc.sh`, then run `ctest -R '^ae_entry/' --output-on-failure`
from the SVF build directory.

The cases cover unknown entry arguments despite a known caller, a custom root
inside a recursive SCC, global initialization and overwrites, exact symbols
with numeric-suffix siblings, and invalid entry requests. Each successful
analysis case runs in dense, semi-sparse and full-sparse modes.

The checker validates diagnostics as well as exit codes: global-value tests
must print two successful assertion verifications and no assertion failure.
This remains effective in Release builds where C/C++ assertions are disabled.
Full-sparse custom-entry runs use AE's conservative dense-memory fallback.
