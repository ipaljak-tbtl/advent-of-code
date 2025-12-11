import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

pts = [list(map(int, line.split(','))) for line in lines]

sol = 0
for r1, c1 in pts:
    for r2, c2 in pts:
        sz = (max(r1, r2) - min(r1, r2)+1) * (max(c1, c2) - min(c1, c2)+1)
        sol = max(sz, sol)

print(sol)
