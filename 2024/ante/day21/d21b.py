#!/usr/bin/env python3

import sys

K1 = '''+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+
'''.splitlines()

K2 = '''    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
'''.splitlines()

KEYS = "<v>^A"
DX = [0, 1, 0, -1]
DY = [-1, 0, 1, 0]


def find(k, t):
    for x, row in enumerate(k):
        for y, c in enumerate(row):
            if c == t:
                return x, y
    assert False

def can_go(k, t, start):
    m = len(k)
    n = len(k[0])
    x, y = start
    res = ''
    for c in t:
        d = KEYS.find(c)
        assert d != -1 and d < 4
        x, y = x+2*DX[d], y+4*DY[d]
        assert 0 <= x < m and 0 <= y < n
        if k[x][y] == ' ':
            return False
    return True


Memo = dict()


def shortest(k, s, n_robots, first=False):
    if n_robots == 0:
        return len(s)
    
    m = len(k)
    n = len(k[0])
    x, y = find(k, 'A')

    if not first:
        if (s, n_robots) in Memo:
            return Memo[(s, n_robots)]

    res = 0
    for c in s:
        xx, yy = find(k, c)
        if yy > y:
            a = '>'*((yy-y)//4)
        else:
            a = '<'*((y-yy)//4)
        if xx < x:
            b = '^'*((x-xx)//2)
        else:
            b = 'v'*((xx-x)//2)
        
        temp = 1e100
        if can_go(k, a+b, (x, y)):
            temp = min(temp, shortest(K2, a+b+'A', n_robots-1))
        if can_go(k, b+a, (x, y)):
            temp = min(temp, shortest(K2, b+a+'A', n_robots-1))
        assert temp != 1e100

        (x, y) = (xx, yy)
        res += temp

    if not first:
        Memo[(s, n_robots)] = res

    return res


def main():
    total = 0
    for t in sys.stdin.readlines():
        t = t.strip()
        if not t:
            continue
        s = shortest(K1, t, 26, True)
        v = int(t[:-1])
        print(t, s, v, s*v)
        total += s*v

    print(total)


if __name__ == "__main__":
    main()