import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))


for i, line in enumerate(lines):
    for j, x in enumerate(line):
        if x == 'S':
            start = (i, j)

mem = dict()
def count(x, y):
    if y < 0 or y >= len(lines[0]):
        return 0
    if x+1 == len(lines):
        return 1
    if (x, y) in mem:
        return mem[(x, y)]
    if lines[x+1][y] == '.':
        mem[(x, y)] = count(x+1, y)
        return mem[(x, y)]

    mem[(x, y)] = count(x+1, y-1) + count(x+1, y+1)

    return mem[(x, y)]

print(count(start[0], start[1]))


