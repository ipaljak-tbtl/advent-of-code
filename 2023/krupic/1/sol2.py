#!/usr/bin/env python3

import sys

strings = {
    'zero': '0',
    'one': '1',
    'two': '2',
    'three': '3',
    'four': '4',
    'five': '5',
    'six': '6',
    'seven': '7',
    'eight': '8',
    'nine': '9',
}

for d in map(str, range(10)):
    strings[d] = d

sol = 0

for line in map(str.rstrip, sys.stdin):
    first = None
    first_idx = None
    last = None
    last_idx = None

    for s, d in strings.items():
        if (idx := line.find(s)) != -1:
            print(f'Found first `{s}` ({d}) in `{line}` at {idx}')
            if not first or first_idx > idx:
                first = d
                first_idx = idx
        if (idx := line.rfind(s)) != -1:
            print(f'Found last `{s}` ({d}) in `{line}` at {idx}')
            if not last or last_idx < idx:
                last = d
                last_idx = idx

    print(first+last)
    sol += int(first+last)
print(sol)
