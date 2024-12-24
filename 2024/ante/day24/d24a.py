#!/usr/bin/env python3

import sys

VALUE = 'value'
AND = 'AND'
OR = 'OR'
XOR = 'XOR'


def evaluate(c, v):
    assert v in c
    if c[v][0] == VALUE:
        return c[v][1]
    op, in1, in2 = c[v]
    if op == AND:
        return evaluate(c, in1) & evaluate(c, in2)
    if op == OR:
        return evaluate(c, in1) | evaluate(c, in2)
    if op == XOR:
        return evaluate(c, in1) ^ evaluate(c, in2)
    assert False
    

def main():
    circuit = {}
    for line in sys.stdin.readlines():
        if ':' in line:
            var, value = line.split(":")
            value = int(value)
            circuit[var] = (VALUE, value)
        elif '->' in line:
            in1, op, in2, _, var = line.split()
            circuit[var] = (op, in1, in2)

    varz = [x for x in circuit.keys() if x.startswith('z')]
    
    sol = 0
    for v in varz:
        i = int(v[1:])
        b = evaluate(circuit, v)
        sol |= (b << i)
    print(sol)


if __name__ == "__main__":
    main()