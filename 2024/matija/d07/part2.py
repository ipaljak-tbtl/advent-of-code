#!/usr/bin/env python3

import sys


def evaluate(test, ns):
    curr = ns[0]

    if len(ns) == 1:
        return curr == test

    e1 = test > curr and evaluate(test - curr, ns[1:])
    e2 = test % curr == 0 and evaluate(test // curr, ns[1:])

    test_s, curr_s = str(test), str(curr)
    e3 = len(test_s) > len(curr_s) and test_s.endswith(
        curr_s) and evaluate(int(test_s.removesuffix(curr_s)), ns[1:])

    return e1 or e2 or e3


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
