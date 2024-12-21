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


def run(k, t, start=None):
    m = len(k)
    n = len(k[0])
    if start is None:
        x, y = find(k, 'A')
    else:
        x, y = start
    res = ''
    for c in t:
        if c == 'A':
            assert k[x][y] in KEYS or k[x][y].isdigit()
            res += k[x][y]
        else:
            d = KEYS.find(c)
            assert d != -1
            x, y = x+2*DX[d], y+4*DY[d]
            assert 0 <= x < m and 0 <= y < n
            assert k[x][y] != ' '
    return res, x, y


def bfs(t):
    x1, y1 = find(K1, 'A')
    x2, y2 = find(K2, 'A')

    Q = [(0, x1, y1, x2, y2, x2, y2, 0)]
    D = set()

    while Q:
        d, x1, y1, x2, y2, x3, y3, i = Q.pop(0)
        for c1 in KEYS:
            xx1, yy1 = x1, y1
            xx2, yy2 = x2, y2
            ii = i
            try:
                c2, xx3, yy3 = run(K2, c1, start=(x3, y3))
                if c2:
                    c3, xx2, yy2 = run(K2, c2, start=(x2, y2))
                    if c3:
                        c4, xx1, yy1 = run(K1, c3, start=(x1, y1))
                        if c4:
                            if c4 != t[i]:
                                continue
                            else:
                                ii = i+1
            except AssertionError:
                continue
            if ii == len(t):
                return d+1
            e = (xx1, yy1, xx2, yy2, xx3, yy3, ii)
            if e in D:
                continue
            D.add(e)
            Q.append((d+1, xx1, yy1, xx2, yy2, xx3, yy3, ii))

    return False


def main():
    total = 0
    for t in sys.stdin.readlines():
        t = t.strip()
        if not t:
            continue
        s = bfs(t)
        v = int(t[:-1])
        print(t, s, v, s*v)
        total += s*v
    print(total)


if __name__ == "__main__":
    main()