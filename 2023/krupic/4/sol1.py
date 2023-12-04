#!/usr/bin/env python3

import sys

def parse_line(line):
    card, nums = line.split(':')
    winning, numbers = map(lambda s: map(int, s.strip().split()), nums.split('|'))
    return set(winning), numbers

total = 0

for line in map(str.rstrip, sys.stdin):
    winning, numbers = parse_line(line)

    score = 0
    for x in numbers:
        if x in winning:
            if score == 0:
                score = 1
            else:
                score *= 2 
    total += score

print(total)

