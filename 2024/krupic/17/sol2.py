#!/usr/bin/env python3

import sys

a = int(input().split()[-1])
b = int(input().split()[-1])
c = int(input().split()[-1])
input()
prog = list(map(int, input().split()[-1].split(',')))

def combo(op, a, b, c):
    if 0 <= op <= 3:
        return op
    return {4: a, 5: b, 6: c}[op]

opcodes = ['adv', 'bxl', 'bst', 'jnz', 'bxc', 'out', 'bdv', 'cdv']

def run(a, suff, b=b, c=c):
    out = []
    ip = 0
    while ip in range(len(prog)):
        opcode, operand = opcodes[prog[ip]], prog[ip+1]
        if opcode in ('adv', 'bdv', 'cdv'):
            v = a >> combo(operand, a, b, c)
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
            b = combo(operand, a, b, c) % 8
        if opcode == 'jnz':
            if a != 0:
                ip = operand
                continue
        if opcode == 'bxc':
            b = b ^ c
        if opcode == 'out':
            out.append(combo(operand, a, b, c) % 8)
            if out[-1] != suff[len(out)-1]:
                return False

        ip += 2
    return out == suff

def rec(a, l):
    for i in range(8):
        if run(a, prog[-l:]):
            if l == len(prog):
                return a
            if (x := rec(a<<3, l+1)) is not None:
                return x
        a += 1

a = rec(0, 1)
assert a is not None and run(a, prog)
print(a)
