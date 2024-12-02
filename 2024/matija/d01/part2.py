#!/usr/bin/env python3

import sys


def main():
    ll, dr = [], {}

    for line in sys.stdin:
        [l, r] = map(int, line.split())
        ll.append(l)
        dr[r] = dr.get(r, 0) + 1

    total = 0

    for l in ll:
        total += l * dr.get(l, 0)

    print(total)


if __name__ == "__main__":
    main()
