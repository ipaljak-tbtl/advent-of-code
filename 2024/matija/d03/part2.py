#!/usr/bin/env python3

import re
import sys


def main():
    memory = sys.stdin.read()

    pattern = r"mul\((\d{1,3}),(\d{1,3})\)|(do|don't)\(\)"

    total = 0
    enabled = True

    for x, y, f in re.findall(pattern, memory):
        if f == "do":
            enabled = True
        elif f == "don't":
            enabled = False
        elif enabled:
            total += int(x) * int(y)

    print(total)


if __name__ == "__main__":
    main()
