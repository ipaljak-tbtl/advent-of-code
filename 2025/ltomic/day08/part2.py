import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

pts = [list(map(int, line.split(','))) for line in lines]

distances = []
for i, x in enumerate(pts):
    for j, y in enumerate(pts):
        if i >= j:
            continue
        distances.append(((x[0]-y[0])**2 + (x[1] - y[1])**2 + (x[2] - y[2])**2, i, j))

distances = sorted(distances, key=lambda x: x[0])

def one(p):
    graph = [[] for _ in range(len(pts))]

    for _, x, y in distances[:p+1]:
        graph[x].append(y)
        graph[y].append(x)

    visited = set()

    def dfs(x):
        visited.add(x)
        for y in graph[x]:
            if y not in visited:
                dfs(y)

    dfs(0)

    if len(visited) == len(pts):
        return True

lo = 0
hi = len(distances)

while lo < hi:
    mid = (lo + hi) // 2

    if one(mid):
        hi = mid
    else:
        lo = mid+1

a = distances[lo][1]
b = distances[lo][2]

print(pts[a][0] * pts[b][0])

