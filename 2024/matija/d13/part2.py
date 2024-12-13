#!/usr/bin/env python3

import sys


total = 0

while True:
    a, c = map(lambda x: int(x[2:]), next(sys.stdin).strip()[10:].split(", "))
    b, d = map(lambda x: int(x[2:]), next(sys.stdin).strip()[10:].split(", "))
    e, f = map(lambda x: int(x[2:]), next(sys.stdin).strip()[7:].split(", "))
    e, f = e + 10_000_000_000_000, f + 10_000_000_000_000

    if ((det := a * d - b * c) and not (de := e * d - b * f) % det
            and not (df := a * f - e * c) % det):
        total += de // det * 3 + df // det

    if next(sys.stdin, False) is False:
        break

print(total)
