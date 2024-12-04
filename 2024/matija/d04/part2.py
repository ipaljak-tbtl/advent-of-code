#!/usr/bin/env python3

import sys


def main():
    grid = list(map(list, map(str.strip, sys.stdin.readlines())))

    total = 0

    for i in range(len(grid) - 2):
        for j in range(len(grid[i]) - 2):
            w1 = grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2]
            w2 = grid[i+2][j] + grid[i+1][j+1] + grid[i][j+2]

            if w1 in ("MAS", "SAM") and w2 in ("MAS", "SAM"):
                total += 1

    print(total)


if __name__ == "__main__":
    main()
