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

visited[('out', True, True)] = 1

def dfs(x, dac, fft):
    if (x, dac, fft) in visited:
        return visited[(x, dac, fft)]
    if x not in graph:
        return 0
    if x == 'dac':
        dac = True
    if x == 'fft':
        fft = True

    sol = 0
    for dist in graph[x]:
        sol += dfs(dist, dac, fft)

    visited[(x, dac, fft)] = sol

    return sol

print(dfs('svr', False, False))
