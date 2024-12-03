#!/usr/bin/env python3

import sys
import re

memory = sys.stdin.read()

r = re.compile("(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))")

sol = 0
do = True
for ins, x, y in r.findall(memory):
    if ins.startswith('mul') and do:
        sol += int(x) * int(y)
    else:
        do = ins == 'do()'

print(sol)

