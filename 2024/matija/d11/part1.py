#!/usr/bin/env python3

import sys


def n_stones(num, blinks):
    if not blinks:
        return 1

    if num == 0:
        return n_stones(1, blinks - 1)
    if (l := len(num_str := str(num))) % 2 == 0:
        return (n_stones(int(num_str[:l//2]), blinks - 1)
                + n_stones(int(num_str[l//2:]), blinks - 1))
    return n_stones(num * 2024, blinks - 1)


n = sum(map(lambda s: n_stones(s, 25), map(int, sys.stdin.read().split())))
print(n)
