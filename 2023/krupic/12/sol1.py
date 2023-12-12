#!/usr/bin/env python3

import sys
import re

def parse_line(line):
    tiles, runs = line.split()
    runs = list(map(int, runs.split(',')))
    return tiles, runs

def rec(count, blocks, f, prefix=''):
    if not blocks:
        return f(prefix + '.' * count)
    head = blocks[0]
    tail = blocks[1:]
    for c in range(count + 1):
        rem = count - c
        new_pref = prefix + '.' * c + head
        rec(rem, tail, f, prefix=new_pref)

def solve(tiles, runs):
    #print(tiles, runs)
    intervals = [x for x in tiles.split('.') if x]
    #print(intervals, len(intervals), len(runs))
    min_len = sum(runs)+len(runs)-1
    slack = len(tiles) - min_len
    #print(len(tiles), min_len, slack)

    blocks = ['#' * b + '.' for b in runs[:-1]] + ['#' * runs[-1]]
    r = re.compile(tiles.replace('.', r'\.').replace('?', '[#.]'))

    def count_sol(s):
        global sol
        if r.fullmatch(s):
            print(s, len(s), len(tiles), tiles)
            sol += 1    

    rec(slack, blocks, count_sol)

sol = 0

for line in sys.stdin:
    solve(*parse_line(line))
print(sol)

