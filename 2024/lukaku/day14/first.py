import sys
import os
import time


poss = []
velo = []

with open(sys.argv[1], 'r') as file:
    for line in file:
        line = line.strip()
        p, v = line.split(' ')

        p = list(map(int, p[len("p="):].split(',')))
        v = list(map(int, v[len("v="):].split(',')))

        poss.append(p)
        velo.append(v)

SECONDS = 100
WIDTH = 101
HEIGHT = 103

q = [0, 0, 0, 0]
for i in range(len(poss)):
    p = poss[i]

    p[0] += SECONDS * velo[i][0]
    p[1] += SECONDS * velo[i][1]

    p[0] %= WIDTH
    p[1] %= HEIGHT
    
    if p[0] < WIDTH // 2 and p[1] < HEIGHT // 2:
        q[0] += 1
    if p[0] > WIDTH // 2 and p[1] < HEIGHT // 2:
        q[1] += 1
    if p[0] < WIDTH // 2 and p[1] > HEIGHT // 2:
        q[2] += 1
    if p[0] > WIDTH // 2 and p[1] > HEIGHT // 2:
        q[3] += 1

print(q[0] * q[1] * q[2] * q[3])

