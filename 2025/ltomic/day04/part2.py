import sys

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

dx = [-1, -1, -1, 0, 1, 1, 1, 0]
dy = [-1, 0, 1, 1, 1, 0, -1, -1]

def outside(lines, x, y):
    return x < 0 or y < 0 or x >= len(lines) or y >= len(lines[0])

lines = [list(line) for line in lines]
def adjacent_rolls(lines, x, y):
    rolls = []
    for px, py in zip(dx, dy):
        nx, ny = x + px, y + py

        if outside(lines, nx, ny):
            continue
        if lines[nx][ny] == '@':
            rolls.append((nx, ny))

    return rolls

cnt = [[0] * len(line) for line in lines]
to_remove = []
for i, line in enumerate(lines):
    for j, c in enumerate(line):
        if c == '@':
            cnt[i][j] = len(adjacent_rolls(lines, i, j))
            if cnt[i][j] < 4:
                to_remove.append((i, j))

sol = 0

while len(to_remove) != 0:
    x, y = to_remove.pop()
    sol += 1

    for ax, ay in adjacent_rolls(lines, x, y):
        cnt[ax][ay] -= 1
        if cnt[ax][ay] == 3:
            to_remove.append((ax, ay))

print(sol)

