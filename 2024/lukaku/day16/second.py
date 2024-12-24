import sys

lab = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        lab.append(line.strip())

rein = None
goal = None
for i in range(len(lab)):
    for j in range(len(lab[0])):
        if lab[i][j] == 'S':
            rein = i, j, 0
        if lab[i][j] == 'E':
            goal = i, j

from queue import PriorityQueue

pq = PriorityQueue()

dpos = [(0, 1), (1, 0), (0, -1), (-1, 0)]

pq.put((0, rein))
mem = dict()
mem[rein] = 0

def check(x, y, d, cost):
    if (x, y, d) in mem and mem[(x, y, d)] <= cost:
        return
    if lab[x][y] == '#':
        return

    pq.put((cost, (x, y, d)))
    mem[(x, y, d)] = cost

while pq.empty() == False: 
    cost, (x, y, d) = pq.get()

    new_x = x + dpos[d][0]
    new_y = y + dpos[d][1]

    check(new_x, new_y, d, cost + 1)
    check(x, y, (d + 1) % 4, cost + 1000)
    check(x, y, (d - 1) % 4, cost + 1000)

visited = set()
tiles = set()

def dfs(x, y, d, cost):
    if (x, y, d, cost) in visited:
        return
    if (x, y, d) not in mem:
        return
    if mem[x, y, d] != cost:
        return

    visited.add((x, y, d))
    tiles.add((x, y))
    new_x = x - dpos[d][0]
    new_y = y - dpos[d][1]

    dfs(new_x, new_y, d, cost-1)
    dfs(x, y, (d + 1) % 4, cost - 1000)
    dfs(x, y, (d - 1) % 4, cost - 1000)

minn = min(mem[goal[0], goal[1], d] for d in range(4))

for d in range(4):
    if mem[goal[0], goal[1], d] == minn:
        dfs(goal[0], goal[1], d, minn)

print(len(tiles))

