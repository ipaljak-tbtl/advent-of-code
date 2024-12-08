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
        return

    antinodes.add((x, y))

def check(i, j, k, l):
    if mapp[i][j] != mapp[k][l]:
        return

    row_diff = k-i
    col_diff = l-j

    add_antinode_if_valid(k + row_diff, l + col_diff)
    add_antinode_if_valid(i - row_diff, j - col_diff)


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
