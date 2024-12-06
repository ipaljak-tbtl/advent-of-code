#!/usr/bin/env python3

import sys


MOVES = [(-1, 0), (0, 1), (1, 0), (0, -1)]


def loop(grid, x, y, move_i, set_x=False):
    visited = set()

    while True:
        if (x, y, move_i) in visited:
            return True

        visited.add((x, y, move_i))

        if set_x and grid[x][y] == ".":
            grid[x][y] = "X"

        dx, dy = MOVES[move_i]
        x += dx
        y += dy

        if not (0 <= x < len(grid) and 0 <= y < len(grid[0])):
            return False

        if grid[x][y] == "#":
            x -= dx
            y -= dy
            move_i = (move_i + 1) % 4


def main():
    grid = list(map(list, map(str.strip, sys.stdin)))

    x, y = 0, 0
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell == "^":
                x, y = i, j

    # set X on visited nodes to mark candidates for obstacle
    loop(grid, x, y, 0, True)

    cnt = 0

    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell == "X":
                row[j] = "#"
                cnt += loop(grid, x, y, 0)
                row[j] = "X"

    print(cnt)


if __name__ == "__main__":
    main()
