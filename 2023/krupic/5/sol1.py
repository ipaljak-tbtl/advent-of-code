#!/usr/bin/env python3

import sys

from collections import ChainMap

def parse_map_line(line):
    dest, source, l = map(int, line.strip().split())
    return lambda x: dest + (x - source) if x in range(source, source+l) else None

def lookup(ms, x):
    for m in ms:
        if (y := m(x)) is not None:
            return y
    return x

def parse_maps():
    ms = []
    for line in map(str.rstrip, sys.stdin):
        if not line:
            yield ms
            ms = []
        elif 'map' in line:
            continue
        else:
            ms.append(parse_map_line(line))
    yield ms


seeds = list(map(int, next(sys.stdin).split(':')[-1].strip().split()))
next(sys.stdin)
maps = list(parse_maps())

def lookup_chain(x):
    for ms in maps:
        x = lookup(ms, x)
    return x

sol = min(seeds, key=lookup_chain)
print(lookup_chain(sol))

