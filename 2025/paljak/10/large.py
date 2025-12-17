from z3 import *

lines = open("in", "r").readlines()

def solve(buttons, target):
    m = len(buttons)
    n = len(target)

    opt = Optimize()

    x = [Int(f"x{j}") for j in range(m)]
    opt.add([xj >= 0 for xj in x])

    for i in range(n):
        opt.add(Sum([x[j] for j, b in enumerate(buttons) if i in b]) == target[i])

    opt.minimize(Sum(x))
    opt.check()

    model = opt.model()
    return sum(model.evaluate(v).as_long() for v in x)

sol = 0
for line in lines:
    tokens = line.replace("(", "[").replace(")", "]").strip().split()
    buttons = [eval(str_button) for str_button in tokens[1:-1]]
    target = tuple(int(x) for x in tokens[-1][1:-1].split(","))
    sol += solve(buttons, target)

print(sol)
