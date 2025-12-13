import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

def solve(lights, buttons, joltage):
    lights = [x == '#' for x in lights[1:-1]]
    buttons = [list(map(int, button[1:-1].split(','))) for button in buttons]

    sol = 100000
    for i in range(1 << len(buttons)):
        state = [False for _ in range(len(lights))]
        cnt = 0
        for j in range(len(buttons)):
            if (i >> j) & 1:
                cnt += 1
                for k in buttons[j]:
                    state[k] ^= True
        if state == lights:
            sol = min(sol, cnt)

    return sol

sol = 0
for line in lines:
    line = line.split()
    lights, buttons, joltage = line[0], line[1:-1], line[-1]
    sol += solve(lights, buttons, joltage)

print(sol)
