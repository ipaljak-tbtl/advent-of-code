import sys
import itertools

puzzle = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        puzzle.append(line.strip())

n = len(puzzle)
m = len(puzzle[0])

dxs = [-1, -1, -1, 0, 1, 1, 1, 0]
dys = [-1, 0, 1, 1, 1, 0, -1, -1]

sol = 0
for x, y in itertools.product(range(n), range(m)):
    for dx, dy in zip(dxs, dys):
        if x+dx*3 < 0 or x+dx*3 >= n or y+dy*3 < 0 or y+dy*3 >= m:
            continue

        candidate = ''.join([puzzle[x+dx*i][y+dy*i] for i in range(4)])

        if candidate == "XMAS":
            sol += 1

print(sol)

