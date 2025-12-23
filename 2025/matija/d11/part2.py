#!/usr/bin/env python3

import sys


def dfs(devices, start, end, mem):
    if start == end:
        return 1

    if start in mem:
        return mem[start]

    mem[start] = sum(dfs(devices, succ, end, mem) for succ in devices[start])

    return mem[start]


devices = {line[0][:-1]: set(line[1:])
           for line in map(lambda l: l.strip().split(), sys.stdin)}
devices["out"] = set()

print(dfs(devices, "svr", "fft", {}) *
      dfs(devices, "fft", "dac", {}) *
      dfs(devices, "dac", "out", {}))
