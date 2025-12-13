import sys
import math
import numpy as np
import scipy

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

def solve(lights, buttons, joltage):
    lights = [x == '#' for x in lights[1:-1]]
    buttons = [list(map(int, button[1:-1].split(','))) for button in buttons]

    joltage = list(map(int, joltage[1:-1].split(',')))

#    print("buttons:", buttons)
#    print("joltage: ", joltage)

    c = np.array([1] * len(buttons))

    A_eq = [[0 for _ in range(len(buttons))] for _ in range(len(joltage))]

    for i, button in enumerate(buttons):
        for x in button:
            A_eq[x][i] = 1

    A_eq = np.array(A_eq)
    b_eq = np.array(joltage)

    bounds = [(0, None) for _ in range(len(buttons))]

#    print(c)
#    print(A_eq)
#    print(b_eq)

    results = scipy.optimize.linprog(c, A_eq=A_eq, b_eq=b_eq, \
            bounds=bounds, integrality=1)

    sol = int(sum(results.x))

    return sol

sol = 0
for line in lines:
    line = line.split()
    lights, buttons, joltage = line[0], line[1:-1], line[-1]
    sol += solve(lights, buttons, joltage)

print(sol)
