#!/usr/bin/env python3

import sys


def main():
    disk = ['.' if i % 2 else i // 2 for i,
            d in enumerate(map(int, sys.stdin.read())) for _ in range(d)]

    total = 0

    l, r = 0, len(disk) - 1
    while l <= r:
        if disk[l] != '.':
            total += l * disk[l]
            l += 1
        elif disk[r] == '.':
            r -= 1
        else:
            total += l * disk[r]
            l += 1
            r -= 1

    print(total)


if __name__ == "__main__":
    main()
