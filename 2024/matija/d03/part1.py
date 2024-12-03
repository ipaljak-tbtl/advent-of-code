#!/usr/bin/env python3

import re
import sys


def main():
    memory = sys.stdin.read()

    pattern = r"mul\((\d{1,3}),(\d{1,3})\)"

    total = 0

    for x, y in re.findall(pattern, memory):
        total += int(x) * int(y)

    print(total)


if __name__ == "__main__":
    main()
