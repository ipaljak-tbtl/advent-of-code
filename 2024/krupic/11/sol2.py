#!/usr/bin/env python3

stones = list(map(int, input().split()))

memo = {}

def rec(x, steps):
    if steps == 0:
        return 1

    if (x, steps) in memo:
        return memo[(x, steps)]

    if x == 0:
        r = memo[(x, steps)] = rec(1, steps-1)
        return r
    if (l := len(s := str(x))) % 2 == 0:
        y, z = map(int, [s[:l//2], s[l//2:]])
        r = memo[(x, steps)] = rec(y, steps-1) + rec(z, steps-1)
        return r
    r = memo[(x, steps)] = rec(x * 2024, steps-1)
    return r

sol = sum(rec(x, 75) for x in stones)
print(sol)

