#!/usr/bin/env python3

import sys


MOVES = [(-1, 0), (0, 1), (1, 0), (0, -1)]


def main():
    grid = list(map(list, map(str.strip, sys.stdin)))

    x, y = 0, 0
    for i, row in enumerate(grid):
        for j, ch in enumerate(row):
            if ch == "^":
                x, y = i, j

    cnt = 1

    move_i = 0

    while True:
        dx, dy = MOVES[move_i]
        x += dx
        y += dy

        if not (0 <= x < len(grid) and 0 <= y < len(grid[0])):
            break

        if grid[x][y] == "#":
            x -= dx
            y -= dy
            move_i = (move_i + 1) % 4
        elif grid[x][y] == ".":
            cnt += 1
            grid[x][y] = "X"

    print(cnt)


if __name__ == "__main__":
    main()
