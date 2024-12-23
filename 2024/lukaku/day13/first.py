import sys
from sage.all import *
from math import isclose

button_a = []
button_b = []
prizes = []

def parse_button(but):
    return list(map(int, but[len("Button A: X+"):].strip().replace(" Y+", "").split(',')))

with open(sys.argv[1], 'r') as file:
    lines = file.readlines()
    for i in range(0, len(lines), 4):
        button_a.append(parse_button(lines[i]))
        button_b.append(parse_button(lines[i+1]))
        prizes.append(list(map(int, lines[i+2].strip()[len("Prize: X="):].replace(" Y=", "").split(','))))



sol = 0
for but_a, but_b, prize in zip(button_a, button_b, prizes):
    p = MixedIntegerLinearProgram(maximization=False, solver='PPL')

    v = p.new_variable(integer=True, nonnegative=True)

    x, y = v['x'], v['y']

    p.set_objective(Integer(3) * x + y)

    p.add_constraint(Integer(but_a[0]) * x + Integer(but_b[0]) * y == prize[0])
    p.add_constraint(Integer(but_a[1]) * x + Integer(but_b[1]) * y == prize[1])

    try: 
        p.solve()
    except:
        continue

    x = p.get_values(x)
    y = p.get_values(y)

    sol += 3 * x + y

print(sol)
