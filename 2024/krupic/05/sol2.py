#!/usr/bin/env python3

import sys
from collections import defaultdict

rules = []
prev = defaultdict(set)
post = defaultdict(set)

while line := input().strip():
    x, y = map(int, line.split('|'))
    rules.append((x, y))
    prev[y].add(x)
    post[x].add(y)

updates = [list(map(int, line.split(','))) for line in sys.stdin]

def valid(update):
    seen_prev = set()
    for x in update:
        if not seen_prev.isdisjoint(post[x]):
            return False
        seen_prev.add(x)

    seen_post = set()
    for x in reversed(update):
        if not seen_post.isdisjoint(prev[x]):
            return False
        seen_post.add(x)

    return True

def toposort(update):
    update = set(update)

    s = []
    v = set()
    def rec(x):
        if x in v:
            return
        v.add(x)
        for y in prev[x]:
            if y in update:
                rec(y)
        s.append(x)

    for x in update:
        rec(x)

    return s

sol = 0
for update in updates:
    if not valid(update):
        assert len(update) % 2 == 1
        update = toposort(update)
        sol += update[len(update)//2]

print(sol)

