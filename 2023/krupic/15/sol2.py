#!/usr/bin/env python3

import sys
import re

def my_hash(s):
    h = 0
    for c in s:
        h = ((h + ord(c)) * 17) & 255
    return h

r = re.compile('([a-z]+)(=\d|-)')

def parse_cmd(c):
    label, op = r.match(c).groups()
    return label, op

strs = next(sys.stdin).strip().split(',')
hmap = [[] for _ in range(256)]

def run_cmd(label, op):
    global hmap
    h = my_hash(label)
    i = next((i for i, (l, _) in enumerate(hmap[h]) if l == label), None)
    if op == '-':
        if i is not None:
            hmap[h].pop(i)
    elif op[0] == '=':
        f = int(op[-1])
        if i is not None:
            hmap[h][i] = (label, f)
        else:
            hmap[h].append((label, f))

for cmd in strs:
    run_cmd(*parse_cmd(cmd))

sol = 0

for i, row in enumerate(hmap):
    for j, (_, f) in enumerate(row):
        sol += (i + 1) * (j + 1) * f

print(sol)

