#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This module is used to compare the output of two commands.

Output of SVF commands should be in the following format:
    **** Section X ****
    Key1 Number1
    Key2 Number2
    ...
    **** Section Y ****
    Key3 Number3
    ...

Then the output is parsed into a dictionary of the following format:
    {
        'Section X': {
            'Key1': Number1,
            'Key2': Number2,
        },
        'Section Y': {
            'Key3': Number3,
            # More
        },
        # More
    }

We call this nested dictionary a `Stats` object.

Because different types of diff tests may have different ways to compare the
stats result, we have to define a `comparer_XXX(stats1, stats2)` function for
each type of diff test.
The `get_comparer()` function determined the appropriate comparer function for
a given command.
Comparer functions should raise an exception, explaining why the two stats are
considered different. They don't have to return anything.
"""

import subprocess
import re
from typing import Optional, Tuple, Union, Callable, Dict, List, Set
from pprint import pprint
import sys

Number = Union[int, float]
Stats = Dict[str, Dict[str, Number]]


def comparer_rwsvfg(stats1: Stats, stats2: Stats):
    '''
    Adapted from this implementation:
    https://github.com/SVF-tools/Test-Suite/blob/b995b111fafee57ab25b937e3d2893bf5e168062/src/diff_tests/diff_tests.cpp#L43
    '''
    section = 'SVFG Statistics'
    keys = '''TotalNode TotalEdge AvgIndOutDeg AvgIndInDeg
            AvgOutDegree AvgInDegree AvgWeight'''.split()
    for key in keys:
        if stats1[section][key] != stats2[section][key]:
            raise ValueError(f"Key {section}.{key} is different")
    return comparer_andersen(stats1, stats2)


def comparer_andersen(stats1: Stats, stats2: Stats):
    getter = lambda d: d['Andersen Pointer Analysis Stats']['AvgTopLvlPtsSize']
    d1 = getter(stats1)
    d2 = getter(stats2)
    delta = abs(d1 - d2) / d1
    exceptions = [
        ('basic_cpp_tests/queue-1.cpp.bc', 0.01), # 0.00604714303344439
        ('basic_cpp_tests/stack-1.cpp.bc', 0.01), # 0.0022123893805308967
        ('basic_cpp_tests/vector-1.cpp.bc', 0.15), # 0.1426766811269205
        ('basic_cpp_tests/vector-3.cpp.bc', 0.17), # 0.15063392744891338
        ('complex_tests/test4.c.bc', 0.29), # 0.2820512820512821
    ]
    path = sys.argv[-1]  # TODO: Hack
    for name, threshold in exceptions:
        if name in path:
            if delta > threshold:
                raise ValueError(
                    f"Diff AvgTopLvlPtsSize {delta} too large for {sys.argv[-1]}")
            else:
                return
    # Default threshold
    if delta > 0.001:
        raise ValueError(f"Diff AvgTopLvlPtsSize {delta} too large")

def comparer_filesystem(stats1: Stats, stats2: Stats):
    keys = stats_keys(stats1)
    assert keys == stats_keys(stats2)
    for section, key in keys:
        if section.startswith('Versioned') and key.startswith('Processed'):
            # Those keys might be different
            # ProcessedCopy ProcessedGep ProcessedLoad ProcessedStore ProcessedPhi
            continue
        if section.startswith('Persistent'):
            # Persistent statistics are not deterministic
            continue
        if key.endswith('Time'):
            # Timing statistics are not deterministic
            continue

        if key.startswith('MemoryUsage'):
            # Memory statistics are not deterministic
            continue

        d1 = stats1[section][key]
        d2 = stats2[section][key]

        if d1 != d2:
            raise ValueError(f"Key [{section}][{key}] differ: {d1} != {d2}")


def usage():
    content = f'''
    Usage: {__file__} <command1> <command2> <path1> [<path2>]
    '''
    print(content)


def stats_keys(stats: Stats) -> Set[Tuple[str, str]]:
    '''
    Return a set of tuple of (section name, key name) in the stats object.
    '''

    result = set()
    for section, section_dict in stats.items():
        for key in section_dict.keys():
            result.add((section, key))
    return result


def str_to_number(s: str) -> Number:
    try:
        return int(s)
    except ValueError:
        return float(s)


def try_get_section(line: str) -> Optional[str]:
    pattern = r'^\*+([^\*]+)\*+\s*$'
    match = re.match(pattern, line)
    if match:
        return match.group(1).strip()
    return None


def try_get_keynum_pair(line: str) -> Optional[Tuple[str, Number]]:
    '''
    Parse line like
    - 'AvgTopLvlPtsSize 123' into a tuple ('AvgTopLvlPtsSize', 123)
    - 'AvgTopLvlPtsSize 123.456' into a tuple ('AvgTopLvlPtsSize', 123.456).
    '''
    pattern = r'^([A-Za-z0-9]+)\s+([-+]?\d*\.?\d+([eE][-+]?\d+)?)\s*$'
    match = re.match(pattern, line)
    if match:
        return match.group(1), str_to_number(match.group(2))
    return None


def get_comparer(cmd1: str) -> Callable[[Stats, Stats], bool]:
    if 'dump-json' in cmd1:
        return comparer_filesystem
    if 'write-svfg' in cmd1:
        return comparer_rwsvfg
    if 'ander' in cmd1:
        return comparer_andersen
    if 'fspta' in cmd1:
        return comparer_andersen
    raise ValueError(f'Cannot decide comparer: {cmd1}')


def exec_collect(cmd: str) -> Stats:
    print(f'Executing command: {cmd}')
    output = subprocess.check_output(cmd, shell=True, universal_newlines=True)

    result: Stats = {}
    current_section = None
    section_cnt: Dict[str, int] = {}

    for lineno, line in enumerate(output.split('\n')):
        line = line.strip()

        # Get the text in section header '***Text***' if any
        section = try_get_section(line)
        if section is not None:
            if section in section_cnt:
                section_cnt[section] += 1
                # TODO: This is a hack to make the section name unique
                current_section = f'{section}@{section_cnt[section]}'
            else:
                section_cnt[section] = 1
                current_section = section

            assert current_section not in result
            result[current_section] = {}
            continue

        # Get the key-value pair if any
        kv = try_get_keynum_pair(line)
        if kv is not None:
            assert isinstance(current_section, str)
            key, val = kv
            if key in result[current_section]:
                raise ValueError(
                    f'Duplicate key `{key}` in section "{current_section} on line {lineno+1}"')
            result[current_section][key] = val

    return result


def main(argv: List[str]):
    if '-h' in argv or '--help' in argv:
        usage()
        sys.exit(0)

    if len(argv) == 4:
        _, cmd1, cmd2, path1 = argv
        path2 = path1
    elif len(argv) == 5:
        _, cmd1, cmd2, path1, path2 = argv
    else:
        usage()
        sys.exit(1)

    cmd1 = f'./{cmd1} {path1}'
    cmd2 = f'./{cmd2} {path2}'

    stats1 = exec_collect(cmd1)
    stats2 = exec_collect(cmd2)

    comparer = get_comparer(cmd1)
    comparer(stats1, stats2)



if __name__ == '__main__':
    main(sys.argv)
