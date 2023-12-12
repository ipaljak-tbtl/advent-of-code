#!/usr/bin/env python3

import sys
import re

from collections import defaultdict

def parse_line(line):
    tiles, runs = line.split()
    runs = list(map(int, runs.split(',')))
    return '?'.join([tiles]*5), runs*5

def solve(tiles, runs):
    # d[run_idx][pattern_idx][tile] where tile := pattern[pattern_idx] if not '?' else tile in '.#'
    d = defaultdict(lambda: defaultdict(lambda: defaultdict(int)))
    d[0][0]['.'] = 1

    for i, tile in enumerate(tiles):
        if tile in '.?':
            d[0][i+1]['.'] = d[0][i]['.']
        else:
            d[0][i+1]['.'] = 0 
        #print(f"d[[]][{tiles[:i+1]}][{'.'}] = {d[0][i+1]['.']}")

    for r in range(len(runs)):
        # compute d[r+1]
        for i, tile in enumerate(tiles):
            # compute d[r+1][i+1]
            if tile in '.?':
                d[r+1][i+1]['.'] = sum(d[r+1][i].values())
                #print(f"d[{runs[:r+1]}][{tiles[:i+1]}][{'.'}] = {d[r+1][i+1]['.']}")
            if tile in '#?':
                last_run = runs[r]
                if i+1 < last_run:
                    continue
                if not all(map(lambda t: t in '#?', tiles[:i+1][-last_run:])):
                    continue
                d[r+1][i+1]['#'] = d[r][i+1 - last_run]['.']
                #print(f"> d[{runs[:r]}][{tiles[:i+1 - last_run]}][{'.'}] = {d[r][i+1 - last_run]['.']}")
                #print(f"d[{runs[:r+1]}][{tiles[:i+1]}][{'#'}] = {d[r+1][i+1]['#']}")

    s = sum(d[len(runs)][len(tiles)].values())
    #print(tiles, runs, s)
    return s

sol = 0

for line in sys.stdin:
    sol += solve(*parse_line(line))
print(sol)
