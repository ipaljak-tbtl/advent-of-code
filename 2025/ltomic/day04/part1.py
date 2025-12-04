import sys

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

dx = [-1, -1, -1, 0, 1, 1, 1, 0]
dy = [-1, 0, 1, 1, 1, 0, -1, -1]

sol = 0

def outside(lines, x, y):
    return x < 0 or y < 0 or x >= len(lines) or y >= len(lines[0])

def adjacent_rolls(lines, x, y):
    cnt = 0
    for px, py in zip(dx, dy):
        nx, ny = x + px, y + py

        if outside(lines, nx, ny):
            continue
        if lines[nx][ny] == '@':
            cnt += 1

    return cnt

for i, line in enumerate(lines):
    for j, c in enumerate(line):
        if c == '@' and adjacent_rolls(lines, i, j) < 4:
            sol += 1

print(sol)

