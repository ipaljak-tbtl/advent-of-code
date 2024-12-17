#!/usr/bin/env python3

from z3 import *


P = [2,4,1,2,7,5,1,3,4,3,5,5,0,3,3,0]


def solve(high):
    A = BitVec('A', 64)
    B = 0
    C = 0
    s = Solver()
    s.add(ULE(A, BitVecVal(high, 64)))
    for x in P:
        # 2,4,
        B = URem(A, 8)
        # 1,2
        B = B ^ 2
        # 7,5
        C = UDiv(A, BitVecVal(1, 64) << B)
        # 1,3
        B = B ^ 3
        # 4,3
        B = B ^ C
        # 5,5
        s.add(URem(B, 8) == x)
        # 0,3
        A = UDiv(A, 8)
        # 3,0
    s.add(A == 0)
    if s.check() == sat:
        return s.model()
    return None


def main():
    lo = 0
    hi = 1<<60
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        s = solve(mid)
        print(mid, s)
        if s:
            hi = mid
        else:
            lo = mid
    print(solve(hi))


if __name__ == "__main__":
    main()
