#!/usr/bin/env python3
"""Run an AE case and check its allocation-size diagnostics against source comments."""

from collections import Counter
from pathlib import Path
import re
import subprocess
import sys


def intervals(pattern, text):
    return Counter((int(lb), int(ub)) for lb, ub in re.findall(pattern, text))


def main():
    if len(sys.argv) < 3:
        print('Usage: check_allocation_bounds.py SOURCE AE [AE_ARGS...]', file=sys.stderr)
        return 1

    source = Path(sys.argv[1]).read_text()
    interval = r'\[\s*(-?\d+)\s*,\s*(-?\d+)\s*\]'
    expected = intervals(r'// EXPECT-ALLOC-SIZE: ' + interval, source)
    known = intervals(r'// KNOWN-ALLOC-SIZE: ' + interval, source)
    no_overflow = '// EXPECT-NO-OVERFLOW' in source
    if bool(expected) == no_overflow or (known and not expected):
        print('Specify allocation bounds or EXPECT-NO-OVERFLOW in the source.', file=sys.stderr)
        return 1

    result = subprocess.run(sys.argv[2:], stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True, errors='replace')
    print(result.stdout, end='')
    if result.returncode != 0:
        print(f'AE exited with status {result.returncode}.', file=sys.stderr)
        return 1

    actual = intervals(r'allocate size\s*:\s*' + interval, result.stdout)
    if actual == expected:
        return 0
    if known and actual == known:
        print(f'SKIP: known allocation-size issue: {dict(actual)}; expected {dict(expected)}.')
        return 77
    print(f'Allocation sizes differ: expected {dict(expected)}, got {dict(actual)}.', file=sys.stderr)
    return 1


if __name__ == '__main__':
    sys.exit(main())
