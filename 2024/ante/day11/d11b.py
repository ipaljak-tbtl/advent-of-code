#!/usr/bin/env python3


Memo = {}


def count(x, n):
    if n == 0:
        return 1
    if (x, n) in Memo:
        return Memo[(x, n)]
    res = 0
    if x == 0:
        res = count(1, n-1)
    elif len(str(x))%2 == 0:
        s = str(x)
        left = s[:len(s)//2]
        right = s[len(s)//2:]
        res = count(int(left), n-1) + count(int(right), n-1)
    else:
        res = count(x*2024, n-1)
    Memo[(x, n)] = res
    return res


def total(s, n):
    res = 0
    for x in s:
        res += count(x, n)
    return res


s = map(int, input().split())
print(total(s, 75))
