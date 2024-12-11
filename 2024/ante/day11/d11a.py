#!/usr/bin/env python3

def blink(s):
    res = []
    for x in s:
        if x == 0:
            res.append(1)
        elif len(str(x))%2 == 0:
            s = str(x)
            left = s[:len(s)//2]
            right = s[len(s)//2:]
            res.extend([int(left), int(right)])
        else:
            res.append(x*2024)
    return res


s = map(int, input().split())
for _ in range(25):
    s = blink(s)
print(len(s))
