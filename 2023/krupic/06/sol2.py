#!/usr/bin/env python3

import sys

from math import sqrt, ceil, floor

times = map(int, next(sys.stdin).split()[1:])
records = map(int, next(sys.stdin).split()[1:])

sol = 1

def discriminant(t, d):
    return t ** 2 - 4 * d

def dist(t, c):
    return c * (t - c)

def solve(t, d):
    sqrt_disc = sqrt(discriminant(t, d))
    lo = floor((t - sqrt_disc) / 2) + 1
    hi = ceil((t + sqrt_disc) / 2) - 1
    assert dist(t, lo) > d
    assert dist(t, hi) > d
    return hi - lo + 1

for time, record in zip(times, records):
    sol *= solve(time, record)

print(sol)

