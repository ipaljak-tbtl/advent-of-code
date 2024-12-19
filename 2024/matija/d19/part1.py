#!/usr/bin/env python3

import sys


def poss(towels, design, mem):
    if design in mem:
        return mem[design]

    for towel in towels:
        if (design.startswith(towel)
                and poss(towels, design[len(towel):], mem)):
            mem[design] = True
            return True

    mem[design] = False
    return False


towels = next(sys.stdin).strip().split(', ')
next(sys.stdin)

total = sum(poss(towels, design.strip(), {"": True}) for design in sys.stdin)
print(total)
