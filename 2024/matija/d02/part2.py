#!/usr/bin/env python3

import sys


def is_safe(report):
    if report[0] > report[1]:
        report.reverse()

    for i in range(len(report) - 1):
        diff = report[i + 1] - report[i]
        if diff < 1 or diff > 3:
            return False

    return True


def main():
    cnt = 0

    for line in sys.stdin:
        report = list(map(int, line.split()))

        for i in range(len(report) + 1):
            if is_safe(report[:i] + report[i+1:]):
                cnt += 1
                break

    print(cnt)


if __name__ == "__main__":
    main()
