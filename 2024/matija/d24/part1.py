#!/usr/bin/env python3

import sys


def calculate(out, gates, calculated):
    if out in calculated:
        return calculated[out]

    in1, op, in2 = gates[out]
    r1 = calculate(in1, gates, calculated)
    r2 = calculate(in2, gates, calculated)
    if op == "AND":
        calculated[out] = r1 & r2
    elif op == "OR":
        calculated[out] = r1 | r2
    else:
        calculated[out] = r1 ^ r2

    return calculated[out]


initial = {}
final = []

line = next(sys.stdin).strip()
while line:
    wire, value = line.split(": ")
    initial[wire] = int(value)
    line = next(sys.stdin).strip()

gates = {}
for line in sys.stdin:
    ins, out = line.strip().split(" -> ")
    gates[out] = tuple(ins.split())
    if out.startswith('z'):
        final.append(out)

final.sort()

calculated = initial.copy()

for out in gates:
    calculate(out, gates, calculated)

result = 0
power = 1
for out in final:
    result += calculated[out] * power
    power *= 2

print(result)
