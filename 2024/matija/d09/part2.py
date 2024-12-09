#!/usr/bin/env python3

import sys


def main():
    disk = [('.' if i % 2 else i // 2, n, 0)
            for i, n in enumerate(map(int, sys.stdin.read()))]

    total = 0

    for i, (idi, ni, _) in reversed(list(enumerate(disk))[1:]):
        if idi != '.':
            cnt = 0
            for j, (idj, nj, offset) in enumerate(disk[:i]):
                cnt += offset
                if idj == '.' and nj >= ni:
                    disk[j] = '.', nj - ni, offset + ni
                    break
                cnt += nj

            total += idi * (ni * (ni-1) // 2 + ni * cnt)

    print(total)


if __name__ == "__main__":
    main()
