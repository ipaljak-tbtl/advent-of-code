import sys
import pulp

def mapin(l):
    splt = l.split(' ')
    jolt = [int(x) for x in splt[-1][1:-1].split(',')]
    buttons = []
    for part in splt[1:-1]:
        btn = [int(x) for x in part[1:-1].split(',')]
        buttons.append(btn)

    return (jolt, buttons)

input = [line.strip() for line in sys.stdin if line.strip()]

input = map(mapin, input)

res = 0
for (joltage, buttons) in input:
    prob = pulp.LpProblem("ButtonJoltageProblem", pulp.LpMinimize)
    vars = [pulp.LpVariable(f"x{i}", lowBound=0, cat='Integer') for i in range(len(buttons))]
    prob += pulp.lpSum(vars)

    for j in range(len(joltage)):
        prob += pulp.lpSum([vars[i] for i in range(len(buttons)) if j in buttons[i]]) == joltage[j]

    prob.solve()
    print(pulp.value(prob.objective))
    res += pulp.value(prob.objective)

print(f"Total: {res}")