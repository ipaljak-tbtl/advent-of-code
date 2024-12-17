#!/usr/bin/env python3

import sys

a = int(input().split()[-1])
b = int(input().split()[-1])
c = int(input().split()[-1])
input()
prog = list(map(int, input().split()[-1].split(',')))

def combo(op):
    if 0 <= op <= 3:
        return op
    return {4: a, 5: b, 6: c}[op]

opcodes = ['adv', 'bxl', 'bst', 'jnz', 'bxc', 'out', 'bdv', 'cdv']

out = []
ip = 0
while ip in range(len(prog)):
    opcode, operand = opcodes[prog[ip]], prog[ip+1]
    if opcode in ('adv', 'bdv', 'cdv'):
        v = a >> combo(operand)
        r = opcode[0]
        if r == 'a':
            a = v
        if r == 'b':
            b = v
        if r == 'c':
            c = v
    if opcode == 'bxl':
        b = b ^ operand
    if opcode == 'bst':
        b = combo(operand) % 8
    if opcode == 'jnz':
        if a != 0:
            ip = operand
            continue
    if opcode == 'bxc':
        b = b ^ c
    if opcode == 'out':
        out.append(combo(operand) % 8)

    ip += 2

print(','.join(map(str, out)))

