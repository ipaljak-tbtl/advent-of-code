import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))


for i, line in enumerate(lines):
    for j, x in enumerate(line):
        if x == 'S':
            start = (i, j)

active = [start]

visited = set([start])
sol = 0
while len(active) != 0:
    x, y = active.pop()

    if x+1 == len(lines):
        continue

    if lines[x+1][y] == '.' and (x+1, y) not in visited:
        active.append((x+1, y))
        visited.add((x+1, y))
    if lines[x+1][y] == '^':
        sol += 1
        def check_add(xx, yy):
            if yy < 0 or yy >= len(lines[0]) or xx == len(lines):
                return
            if (xx, yy) in visited:
                return
            active.append((xx, yy))

        check_add(x+1, y-1)
        check_add(x+1, y+1)

print(sol)
