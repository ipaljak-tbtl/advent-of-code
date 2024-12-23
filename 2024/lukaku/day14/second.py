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

sec = 0
for sec in range(1, 9000):
    for i in range(len(poss)):
        poss[i][0] += velo[i][0]
        poss[i][1] += velo[i][1]

        poss[i][0] %= WIDTH
        poss[i][1] %= HEIGHT
    
    p = set(map(tuple, poss))

    for y in range(HEIGHT):
        for x in range(WIDTH):
            if (x, y) in p:
                print("X", end='')
            else:
                print(".", end='')
        print()

    print(sec)


