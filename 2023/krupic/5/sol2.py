#!/usr/bin/env python3

import sys

from collections import namedtuple

Fn = namedtuple('Fn', ('y', 'x', 'l'))
Interval = namedtuple('Interval', ('x', 'l'))

def parse_map_line(line):
    dest, source, l = map(int, line.strip().split())
    return Fn(y=dest, x=source, l=l) 

def parse_maps():
    ms = []
    for line in map(str.rstrip, sys.stdin):
        if not line:
            yield sorted(ms, key=lambda m: m.x)
            ms = []
        elif 'map' in line:
            continue
        else:
            ms.append(parse_map_line(line))
    yield ms

def parse_seeds():
    numbers = list(map(int, next(sys.stdin).split(':')[-1].strip().split()))
    intervals = []
    for i in range(0, len(numbers), 2):
        x, l = numbers[i:i+2]
        intervals.append(Interval(x=x, l=l))
    next(sys.stdin)
    return intervals

def apply(fn, xi):
    lo = max(fn.x, xi.x)
    hi = min(fn.x + fn.l, xi.x + xi.l)
    if lo < hi:
        return Interval(x=fn.y + (lo - fn.x), l=hi-lo)
    else:
        assert False

def lookup(ms, xis):
    ms = ms.copy()
    for xi in sorted(xis, key=lambda xi: xi.x):
        start = xi.x
        end = xi.x + xi.l

        while ms and start < end:
            while ms and ms[0].x + ms[0].l <= start:
                ms.pop(0)
            # start < ms[0].end or ms is empty

            if not ms:
                break
            # start < ms[0].end

            if start < ms[0].x:
                hi = min(ms[0].x, end)
                # identity fn of [start, hi>
                yield Interval(x=start, l=hi-start)
                if hi == end:
                    # start < end < ms[0].x < ms[0].end
                    # done with whole interval
                    break
                # start < ms[0].x < end
                start = ms[0].x
                # start == ms[0].x < end

            m_end = ms[0].x + ms[0].l
            if m_end < end:
                # ms[0] of [start, m_end>
                yield apply(ms[0], Interval(x=start, l=m_end-start))
                ms.pop(0)
                # ms[0] is used up, interval isnt
                start = m_end
                continue
            else:
                # ms[0] of [start, end>
                yield apply(ms[0], Interval(x=start, l=end-start))
                # interval is used up, ms[0] may or may not be
                start = end
                break
        # not ms or done with interval
        if start < end:
            yield Interval(x=start, l=end-start)

seeds = parse_seeds()
maps = list(parse_maps())

def lookup_chain(xis):
    for ms in maps:
        xis = lookup(ms, xis)
    return xis

res = lookup_chain(seeds)
sol = min(i.x for i in res)
print(sol)

