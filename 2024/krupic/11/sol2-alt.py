#!/usr/bin/env python3

from collections import Counter

stones = Counter(map(int, input().split()))

def step(x):
    if x == 0:
        return [1]
    if (l := len(s := str(x))) % 2 == 0:
        return map(int, [s[:l//2], s[l//2:]])
    return [x * 2024]

for it in range(75):
    new = Counter()
    for x, c in stones.items():
        for y in step(x):
            new[y] += c
    stones = new

print(sum(stones.values()))

