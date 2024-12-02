#!/usr/bin/env python3

import sys


def main():
    ll, lr = [], []

    for line in sys.stdin:
        [l, r] = map(int, line.split())
        ll.append(l)
        lr.append(r)

    total = 0

    for (l, r) in zip(sorted(ll), sorted(lr)):
        total += abs(l - r)

    print(total)


if __name__ == "__main__":
    main()
