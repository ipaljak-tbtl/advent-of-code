#!/usr/bin/env python3

import sys


def evaluate(test, ns):
    curr = ns[0]

    if len(ns) == 1:
        return curr == test

    e1 = test > curr and evaluate(test - curr, ns[1:])
    e2 = test % curr == 0 and evaluate(test // curr, ns[1:])

    return e1 or e2


def main():
    total = 0

    for line in sys.stdin:
        test, ns = line.split(": ")
        ns = list(map(int, reversed(ns.split())))
        test = int(test)

        if evaluate(test, ns):
            total += test

    print(total)


if __name__ == "__main__":
    main()
