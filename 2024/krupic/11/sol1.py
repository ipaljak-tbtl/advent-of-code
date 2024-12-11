#!/usr/bin/env python3

stones = list(map(int, input().split()))

def step(x):
    if x == 0:
        return [1]
    if (l := len(s := str(x))) % 2 == 0:
        return map(int, [s[:l//2], s[l//2:]])
    return [x * 2024]

for it in range(25):
    print(it, stones)
    new = []
    for x in stones:
        new.extend(step(x))
    stones = new

print(len(stones))

