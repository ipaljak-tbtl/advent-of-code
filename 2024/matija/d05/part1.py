#!/usr/bin/env python3

import sys


def main():
    rules = {}

    line = next(sys.stdin).strip()
    while line:
        x, y = map(int, line.split("|"))

        rules.setdefault(y, set()).add(x)

        line = next(sys.stdin).strip()

    total = 0

    for line in sys.stdin:
        pages = list(map(int, line.split(",")))

        for i in range(1, len(pages)):
            for j in range(i):
                if pages[i] in rules.get(pages[j], set()):
                    break
            else:
                continue
            break
        else:
            total += pages[len(pages)//2]

    print(total)


if __name__ == "__main__":
    main()
