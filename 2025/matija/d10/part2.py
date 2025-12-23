#!/usr/bin/env python3

import sys
from z3 import IntVector, Optimize, Sum

res = 0

for line in map(lambda l: l.strip().split(), sys.stdin):
    wires = [set(map(int, x[1:-1].split(","))) for x in line[1:-1]]
    jolts = list(map(int, line[-1][1:-1].split(",")))

    opt = Optimize()

    c_max = sum(jolts)
    cs = IntVector("c", len(wires))
    for c in cs:
        opt.add(c >= 0, c <= c_max)

    for j, jolt in enumerate(jolts):
        opt.add(Sum([c for i, c in enumerate(cs) if j in wires[i]]) == jolt)

    opt.minimize(Sum(cs))
    opt.check()
    model = opt.model()
    res += model.evaluate(Sum(cs)).as_long()

print(res)
