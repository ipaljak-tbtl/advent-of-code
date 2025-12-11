import sys
import math
from tqdm import tqdm

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

pts = [list(map(int, line.split(','))) for line in lines]

verticals = []

for i, ((c1, r1), (c2, r2)) in enumerate(zip(pts, pts[1:] + pts[:1])):
    if r1 == r2:
        continue
    verticals.append((c1, r1, r2))

verticals = sorted(verticals, key=lambda x: x[0])

state = []
last_x = -1

def update(state, vert):
    if vert[1] > vert[2]:
        return update_open(state, (vert[0], vert[2], vert[1]))
    else:
        return update_close(state, vert)

def update_open(state, vert):
    new_state = state + [vert]

    return new_state

def update_close(state, vert):
    new_state = []
    x, u, d = vert
    u += 1
    d -= 1
    for (xx, uu, dd) in state:
        if uu > dd:
            continue
        if dd < u or uu > d:
            new_state.append((xx, uu, dd))
            continue
        upper = (xx, uu, u-1)
        lower = (xx, d+1, dd)

        if upper[1] <= upper[2]:
            new_state.append(upper)
        if lower[1] <= lower[2]:
            new_state.append(lower)

    return new_state

def inside(state, last_x, ul, lr):
    if lr[0] > last_x:
        return False

    intervals = []
    for x, u, d in state:
        if x > ul[0]:
            continue
        intervals.append((u, 0))
        intervals.append((d+1, 1))

    intervals = sorted(intervals)
    cnt = 0
    open_y = -1
    for y, e in intervals:
        if e == 0:
            if cnt == 0:
                open_y = y
            cnt += 1
        if e == 1:
            cnt -= 1
            if open_y <= ul[1] and y >= lr[1]:
                return True

    return False

tested = set()

def get_largest(state, last_x, pts):
    sol = 0

    for i, (c1, r1) in enumerate(pts):
        for c2, r2 in pts[i:]:
            ul = (min(c1, c2), min(r1, r2))
            lr = (max(c1, c2), max(r1, r2))

            if (ul, lr) in tested:
                continue

            if inside(state, last_x, ul, lr):
                tested.add((ul, lr))
                sol = max(sol, (lr[0] - ul[0] + 1) * (lr[1] - ul[1] + 1))

    return sol

    
sol = 0
print(len(verticals))
for i, vert in tqdm(enumerate(verticals)):
    sol = max(sol, get_largest(state, last_x, pts))

    last_x = vert[0]
    state = update(state, vert)

sol = max(sol, get_largest(state, last_x, pts))

print(sol)
