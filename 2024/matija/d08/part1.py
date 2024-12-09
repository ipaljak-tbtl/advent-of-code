#!/usr/bin/env python3

import sys


def main():
    grid = list(map(list, map(str.strip, sys.stdin)))
    n = len(grid)

    antennas = {}

    used = set()

    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if c != ".":
                for ai, aj in antennas.get(c, []):
                    ti, tj = 2*i - ai, 2*j - aj
                    if 0 <= ti < n and 0 <= tj < n:
                        used.add((ti, tj))

                    ti, tj = 2*ai - i, 2*aj - j
                    if 0 <= ti < n and 0 <= tj < n:
                        used.add((ti, tj))

                antennas.setdefault(c, []).append((i, j))

    print(len(used))


if __name__ == "__main__":
    main()
