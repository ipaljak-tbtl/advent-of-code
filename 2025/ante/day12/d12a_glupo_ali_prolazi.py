#!/usr/bin/env python3
 
import sys

NTILES = 6

def convert(tile):
    T = set()
    for i in range(3):
        for j in range(3):
            if tile[i][j] == '#':
                T.add((i, j))
    return T


def solve_or(tiles, counts, m, n):
    total = 0
    for i in range(NTILES):
        total += counts[i]*len(tiles[i])
    if total > m*n:
        return False
    return True


if __name__ == "__main__":
    total = 0
    lines = sys.stdin.readlines()
    tiles = [convert(lines[5*i+1:5*i+4]) for i in range(NTILES)]
    for line in lines[30:]:
        items = line.split()
        counts = list(map(int, items[1:]))
        m, n = map(int, items[0][:-1].split('x'))
        if solve_or(tiles, counts, m, n):
            total += 1
    
    print(total)
