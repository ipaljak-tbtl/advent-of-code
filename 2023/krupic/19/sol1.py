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

def parse_part(line):
    kvs = map(lambda kv: kv.split('='), line[1:-1].split(','))
    return {k: int(v) for k, v in kvs}

lines = list(map(str.strip, sys.stdin))
i = lines.index('')
workflows = dict(map(parse_workflow, lines[:i]))
parts = list(map(parse_part, lines[i+1:]))

def interpret(part, wf):
    for guard, target in wf:
        if guard:
            key, cond, y = guard
            x = part[key]
            if cond == '<' and not x < y:
                continue
            if cond == '>' and not x > y:
                continue
        if target == 'A':
            return True
        if target == 'R':
            return False
        return target

def solve_part(part):
    wf = workflows['in']
    while type(r := interpret(part, wf)) is not bool:
        wf = workflows[r]
    return sum(part.values()) if r else 0

sol = sum(map(solve_part, parts))
print(sol)

