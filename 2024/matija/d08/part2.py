#!/usr/bin/env python3

import sys


def gcd(a, b):
    while b:
        a, b = b, a % b
    return abs(a)


def main():
    grid = list(map(list, map(str.strip, sys.stdin)))
    n = len(grid)

    antennas = {}

    used = set()

    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if c != ".":
                for ai, aj in antennas.get(c, []):
                    d = gcd(i - ai, j - aj)
                    di, dj = (i - ai) // d, (j - aj) // d

                    for m in [1, -1]:
                        ti, tj = i, j
                        while 0 <= ti < n and 0 <= tj < n:
                            used.add((ti, tj))
                            ti, tj = ti + m*di, tj + m*dj

                antennas.setdefault(c, []).append((i, j))

    print(len(used))


if __name__ == "__main__":
    main()
