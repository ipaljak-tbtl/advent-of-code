import sys
import math
import numpy as np
import scipy

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

graph = dict()
for line in lines:
    x, dists = line.split(':')
    graph[x] = dists.split()

visited = dict()

visited['out'] = 1

def dfs(x):
    if x in visited:
        return visited[x]

    sol = 0
    for dist in graph[x]:
        sol += dfs(dist)

    visited[x] = sol

    return sol

print(dfs('you'))
