#!/usr/bin/env python3

import sys


T = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]


def main():
    grid = list(map(list, map(str.strip, sys.stdin.readlines())))

    total = 0

    for i, row in enumerate(grid):
        for j in range(len(row)):
            for dr, dc in T:
                r, c = i, j
                word = ""

                for _ in range(4):
                    word += grid[r][c]

                    r += dr
                    c += dc

                    if r < 0 or r >= len(grid) or c < 0 or c >= len(grid[r]):
                        break

                if word == "XMAS":
                    total += 1

    print(total)


if __name__ == "__main__":
    main()
