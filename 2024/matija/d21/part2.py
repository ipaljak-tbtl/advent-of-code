#!/usr/bin/env python3

import sys

rs = {
    '^': (-1, 0),
    '<': (0, -1),
    'v': (1, 0),
    '>': (0, 1),
}

keys = [[
    ['7', '8', '9'],
    ['4', '5', '6'],
    ['1', '2', '3'],
    [None, '0', 'A'],
], [
    [None, '^', 'A'],
    ['<', 'v', '>'],
]]

mem_keys, mem_paths, mem_lens = {}, {}, {}


def find(k_i, elem):
    if (k_i, elem) in mem_keys:
        return mem_keys[k_i, elem]

    for i, row in enumerate(keys[k_i]):
        for j, c in enumerate(row):
            if c == elem:
                mem_keys[k_i, elem] = i, j
                return i, j


def get_paths(start, end, k_i):
    if start == end:
        return 'A'
    if (k_i, start, end) in mem_paths:
        return mem_paths[k_i, start, end]

    si, sj = find(k_i, start)
    ei, ej = find(k_i, end)
    ds = abs(si - ei) + abs(sj - ej)

    paths = []
    for r, (di, dj) in rs.items():
        ni, nj = si + di, sj + dj
        if abs(ni - ei) + abs(nj - ej) < ds and keys[k_i][ni][nj]:
            for path in get_paths(keys[k_i][ni][nj], end, k_i):
                paths.append(r + path)

    mem_paths[k_i, start, end] = paths
    return paths


def length(code, d, k_i):
    if d == 0:
        return len(code)
    if (code, d) in mem_lens:
        return mem_lens[code, d]

    min_len = 0
    for i, c in enumerate('A' + code[:-1]):
        min_len += min(length(p, d-1, 1) for p in get_paths(c, code[i], k_i))

    mem_lens[code, d] = min_len
    return min_len


total = sum(int(c[:-1]) * length(c, 26, 0) for c in map(str.strip, sys.stdin))
print(total)
