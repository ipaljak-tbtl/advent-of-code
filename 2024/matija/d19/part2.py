#!/usr/bin/env python3

import sys


def arrs(towels, design, mem):
    if design in mem:
        return mem[design]

    total = 0
    for towel in towels:
        if design.startswith(towel):
            total += arrs(towels, design[len(towel):], mem)

    mem[design] = total

    return total


towels = next(sys.stdin).strip().split(', ')
next(sys.stdin)

total = sum(arrs(towels, design.strip(), {"": 1}) for design in sys.stdin)
print(total)
