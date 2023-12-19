#!/usr/bin/env python3

import sys

delta = {
    'U': (-1, 0),
    'D': (1, 0),
    'L': (0, -1),
    'R': (0, 1)
}

def parse_line(line):
    _, _, ins = line.strip().split()
    ins = ins[2:-1]
    d = 'RDLU'[int(ins[-1])]
    steps = int(ins[:-1], 16)
    return d, steps

steps = list(map(parse_line, sys.stdin))
N = len(steps)
i, j = 0, 0

border = 0
for d, n in steps:
    di, dj = delta[d]
    i += di * n
    j += dj * n
    border += n

sol = 0
for k, (d, n) in enumerate(steps):
    di, dj = delta[d]
    n_i = i + di * n
    n_j = j + dj * n
    prev_s = steps[(k - 1) % N][0]
    next_s = steps[(k + 1) % N][0]
    if d == 'R':
        c = n - 1
        c += prev_s == 'D'
        c += next_s == 'U'
        sol += c * (- i)
    if d == 'L':
        c = n - 1
        c += prev_s == 'U'
        c += next_s == 'D'
        sol -= c * (- i + 1)
    i, j = n_i, n_j
sol = sol + border
print(sol)

