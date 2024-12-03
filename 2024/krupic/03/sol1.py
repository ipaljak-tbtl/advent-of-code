#!/usr/bin/env python3

import sys
import re

memory = sys.stdin.read()

r = re.compile('mul\((\d{1,3}),(\d{1,3})\)')

sol = 0
for x, y in r.findall(memory):
    sol += int(x) * int(y)

print(sol)
