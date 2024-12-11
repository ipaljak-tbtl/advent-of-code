#!/usr/bin/env python3

import sys


def n_stones(num, blinks, mem):
    if not blinks:
        return 1

    if (num, blinks) in mem:
        return mem[num, blinks]

    if num == 0:
        mem[num, blinks] = n_stones(1, blinks - 1, mem)
    elif (l := len(num_s := str(num))) % 2 == 0:
        mem[num, blinks] = (n_stones(int(num_s[:l//2]), blinks - 1, mem)
                            + n_stones(int(num_s[l//2:]), blinks - 1, mem))
    else:
        mem[num, blinks] = n_stones(num * 2024, blinks - 1, mem)

    return mem[num, blinks]


n = sum(map(lambda s: n_stones(s, 75, {}), map(int, sys.stdin.read().split())))
print(n)
