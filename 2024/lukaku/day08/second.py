import sys

mapp = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        mapp.append(line.strip())

n = len(mapp)
m = len(mapp[0])

antinodes = set()

def add_antinode_if_valid(x, y):
    if x < 0 or y < 0 or x >= n or y >= m:
        return False

    antinodes.add((x, y))

    return True

def check(a, b, c, d):
    if mapp[a][b] != mapp[c][d]:
        return

    row_diff = c-a
    col_diff = d-b

    k = 0
    while True:
        if add_antinode_if_valid(c + k * row_diff, d + k * col_diff) == False:
            break
        k += 1
        
    k = -1
    while True:
        if add_antinode_if_valid(c + k * row_diff, d + k * col_diff) == False:
            break
        k -= 1

for i in range(n):
    for j in range(m):
        if mapp[i][j] == '.':
            continue

        for k in range(i+1, n):
            for l in range(m):
                check(i, j, k, l)

        for l in range(j+1, m):
            check(i, j, k, l)

print(len(antinodes))
