#!/usr/bin/env python3

import sys
from math import ceil, floor

def parse_line(line, sep):
    return map(lambda s: int(s.split(sep)[-1]) , line.strip().split(': ')[-1].split(', '))

def parse_one(lines):
    ax, ay = parse_line(lines.pop(0), '+')
    bx, by = parse_line(lines.pop(0), '+')
    cx, cy = parse_line(lines.pop(0), '=')
    try:
        lines.pop(0)
    except:
        pass
    return (ax, bx, cx), (ay, by, cy)

def add_mul(v1, v2, k):
    return tuple(a + k * b for a, b in zip(v1,v2))

def solve_sys(eq1, eq2):
    while True:
        if eq1[0] == 0:
            if eq1[1:] == (0, 0):
                return solve(*eq2)
            elif eq1[1] == 0:
                pass
            else:
                if eq1[2] % eq1[1] == 0:
                    b = eq1[2] // eq1[1]
                    t = eq2[2] - eq2[1] * b
                    if t % eq2[0] == 0:
                        a = t // eq2[0]
                        return a, b
            return

        eq2 = add_mul(eq2, eq1, - (eq2[0] // eq1[0]))
        eq1, eq2 = eq2, eq1

def ext_gcd(a, b, c):
    if a == 0:
        if c % b == 0:
            return (0, c // b, b)
        else:
            return None

    a_ = b % a
    b_ = a
    if r := ext_gcd(a_, b_, c):
        x_, y_, gcd = r
        y = x_
        x = y_ - b // a * y
        assert a * x + b * y == c
        return (x, y, gcd)
    else:
        return None

def solve(a, b, c):
    r = ext_gcd(a, b, c)
    if not r:
        return None
    x0, y0, gcd = r

    da = b // gcd
    db = a // gcd

    if da == 0:
        return (x0, y0)
    elif da > 0:
        k = ceil(-x0 / da)
    else:
        k = floor(-x0 / da)
    x = x0 + k * da
    y = y0 - k * db
    return (x, y)
        


def main():
    lines = sys.stdin.readlines()
    sol = 0
    while lines:
        eqx, eqy = parse_one(lines)
        if ab := solve_sys(eqx, eqy):
            a, b = ab
            assert eqx[0] * a + eqx[1] * b == eqx[2]
            assert eqy[0] * a + eqy[1] * b == eqy[2]
            sol += 3 * a + b  
    print(sol)
    

if __name__ == '__main__':
    main()

