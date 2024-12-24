#!/usr/bin/env python3

import sys
import random

VALUE = 'value'
AND = 'AND'
OR = 'OR'
XOR = 'XOR'

X = lambda i: 'x{:02d}'.format(i)
Y = lambda i: 'y{:02d}'.format(i)
Z = lambda i: 'z{:02d}'.format(i)


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


def evalint(c, x, y, k):
    for i in range(k):
        c[X(i)] = (VALUE, (x>>i)&1)
        c[Y(i)] = (VALUE, (y>>i)&1)
    r = 0
    for i in range(k):
        v = evaluate(c, Z(i))
        r |= (v<<i)
    return r


def depends(c, v):
    assert v in c
    if c[v][0] == VALUE:
        return set([v])
    op, in1, in2 = c[v]
    return set([v]) | depends(c, in1) | depends(c, in2)


def check(c, k):
    d = c.copy()
    for i in range(100):
        xi = X(i)
        yi = Y(i)
        if xi in d:
            d[xi] = (VALUE, None)
        if yi in d:
            d[yi] = (VALUE, None)
    for i in range(1000):
        x = random.randint(0, 2**k-1)
        y = random.randint(0, 2**k-1)
        try:
            z = evalint(d, x, y, k)
        except (TypeError, RecursionError):
            return False 
        if z != (x+y) % (2**k):
            return False
    return True


def find_swaps(c):
    swapped = set()
    all = set()
    for k in range(45):
        if check(c, k):
            print(f'Good {k=}')
            continue
        print(f'Attempting to fix {k=}')
        candidates = depends(c, Z(k)) - depends(c, Z(k-1))
        done = False
        for a in candidates:
            for b in c.keys():
                if done:
                    continue
                if a == b or a in swapped or b in swapped:
                    continue
                if b.startswith('x') or b.startswith('y'):
                    continue
                if a.startswith('x') or a.startswith('y'):
                    continue
                d = c.copy()
                d[a], d[b] = d[b], d[a]
                if check(d, k):
                    print(f'Fixed! {k=} {a=} {b=}')
                    swapped.add(a)
                    swapped.add(b)
                    c = d
                    done = True
        assert(done)
    print(','.join(sorted(all)))


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

    find_swaps(circuit)


if __name__ == "__main__":
    main()