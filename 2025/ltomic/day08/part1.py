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

graph = [[] for _ in range(len(pts))]

for _, x, y in distances[:1000]:
    graph[x].append(y)
    graph[y].append(x)

visited = set()

def dfs(x):
    sol = 1
    for y in graph[x]:
        if y not in visited:
            visited.add(y)
            sol += dfs(y)
    return sol

circut_size = []
for i in range(len(pts)):
    if i not in visited:
        visited.add(i)
        circut_size.append(dfs(i))

print(math.prod(list(reversed(sorted(circut_size)))[:3]))
