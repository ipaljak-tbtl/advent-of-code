#!/usr/bin/env python3

import sys
from collections import defaultdict, deque

def parse_line(line):
    module, outputs = line.strip().split(' -> ')
    outputs = outputs.strip().split(', ')
    mod_type = None
    if module[0] in '%&':
        mod_type = module[0]
        module = module[1:]
    return module, (mod_type, outputs)

modules = dict(map(parse_line, sys.stdin))
inputs = defaultdict(list)
for m_in, (_, outputs) in modules.items():
    for m_out in outputs:
        inputs[m_out].append(m_in)
states = dict()
for m, (mod_type, _) in modules.items():
    if mod_type == '%':
        states[m] = False
    elif mod_type == '&':
        states[m] = {m_in: False for m_in in inputs[m]}

def process_msg(m, source, pulse):
    if m not in modules:
        return []
    mod_type, outputs = modules[m]
    if mod_type == '%':
        if pulse:
            return []
        else:
            s = not states[m]
            states[m] = s
            return [(out, m, s) for out in outputs]
    elif mod_type == '&':
        states[m][source] = pulse
        out_pulse = not all(states[m].values())
        return [(out, m, out_pulse) for out in outputs]
    else:
        assert m == 'broadcaster'
        return [(out, m, pulse) for out in outputs]

def simulate_round():
    count = {False: 0, True: 0}
    q = deque()
    q.append(('broadcaster', None, False))
    while q:
        msg = q.popleft()
        count[msg[2]] += 1
        print(f'{msg[1]} -{msg[2]}-> {msg[0]}')
        for new_msg in process_msg(*msg):
            q.append(new_msg)
    return count

count = {False: 0, True: 0}
for _ in range(1000):
    for k, v in simulate_round().items():
        count[k] += v
print(count[False], count[True])
sol = count[False] * count[True]
print(sol)

