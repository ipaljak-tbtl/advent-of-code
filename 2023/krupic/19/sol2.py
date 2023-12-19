#!/usr/bin/env python3

import sys

def parse_rule(rule):
    parts = rule.split(':')
    if len(parts) == 1:
        return (None, *parts)
    cond, target = parts
    return ((cond[0], cond[1], int(cond[2:])), target)

def parse_workflow(line):
    line = line.strip()
    brace = line.find('{')
    name = line[:brace]
    rules = [parse_rule(r) for r in line[brace+1:-1].split(',')]
    return name, rules

lines = list(map(str.strip, sys.stdin))
i = lines.index('')
workflows = dict(map(parse_workflow, lines[:i]))

neg = {'<': '>=', '>': '<='}
def negate(b):
    key, cond, y = b
    return key, neg[cond], y

def affirm(b):
    key, cond, y = b
    if cond == '<':
        return key, '<=', y - 1
    if cond == '>':
        return key, '>=', y + 1
    return b

DEFAULT = {k: (1, 4000) for k in 'xmas'}

def update(bounds, b):
    key, cond, y = b
    if cond == '>=':
        lo, hi = bounds[key]
        bounds[key] = (max(lo, y), hi)
    if cond == '<=':
        lo, hi = bounds[key]
        bounds[key] = (lo, min(hi, y))

def combinations(bounds):
    r = 1
    for lo, hi in bounds.values():
        r *= max(hi - lo + 1, 0)
    return r

def interpret(bounds, wf):
    if wf == 'A':
        return combinations(bounds)
    if wf == 'R':
        return 0

    r = 0
    for guard, target in workflows[wf]:
        if guard:
            # guard true
            bs = bounds.copy()
            update(bs, affirm(guard))
            r += interpret(bs, target)

            # guard false
            update(bounds, negate(guard))
        else:
            r += interpret(bounds, target)
            break
    return r

sol = interpret(DEFAULT, 'in')
print(sol)

