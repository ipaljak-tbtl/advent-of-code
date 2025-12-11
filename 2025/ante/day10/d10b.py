import sys

from ortools.sat.python import cp_model


def parse(line):
    items = line.split()
    levels = list(map(int, items[-1][1:-1].split(',')))
    switches = [list(map(int, x[1:-1].split(','))) for x in items[1:-1]]
    return levels, switches


def solve(levels, switches):
    model = cp_model.CpModel()
    n = len(levels)
    m = len(switches)
    max_level = max(levels)

    x = [model.NewIntVar(0, max_level, f'x{i}') for i in range(m)]

    for i in range(n):
        model.Add(sum(x[j] for j in range(m) if i in switches[j]) == levels[i])

    model.Minimize(sum(x))

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    assert(status == cp_model.OPTIMAL)
    return int(solver.ObjectiveValue())


if __name__ == "__main__":
    total = 0
    for line in sys.stdin.readlines():
        levels, switches = parse(line)
        total += solve(levels, switches)
    print(total)