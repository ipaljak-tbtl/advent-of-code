#!/usr/bin/env python3

import sys
from collections import defaultdict, deque

delta = [(-1, 0), (1, 0), (0, -1), (0, 1)]

grid = list(map(str.strip, sys.stdin))
rows = cols = 131
origin = (65, 65)
T = 26501365
assert T % rows == 65
assert not any(grid[65][j] == '#' for j in range(cols))
assert not any(grid[i][65] == '#' for i in range(rows))

midpoints = [(i*65 + 65, j*65 + 65) for i, j in delta]
corners = [(i, j) for i in (0, 130) for j in (0, 130)]


def adj_iter(i, j):
    for di, dj in delta:
        ni, nj = i + di, j + dj
        if 0 <= ni < rows and 0 <= nj < cols and grid[ni][nj] != '#':
            yield ni, nj

def bfs(start):
    visit_time = [1]
    visited = {start}
    front = {start}
    while front:
        front = {npos for pos in front for npos in adj_iter(*pos) if npos not in visited}
        visited |= front
        if front:
            visit_time.append(len(front))
    return visit_time

midpoint_fronts = {p: bfs(p) for p in midpoints}
corner_fronts = {p: bfs(p) for p in corners}
fronts = {**midpoint_fronts, **corner_fronts, origin: bfs(origin)}
cover_time = {p: len(fs) - 1 for p, fs in fronts.items()}

B = T // rows

def block_of(i, j):
    return (i // rows, j // cols), (i % rows, j % cols)

def block_start_pos_times(bi, bj):
    i = rows // 2 if bi == 0 else 0 if bi > 0 else rows - 1
    j = cols // 2 if bj == 0 else 0 if bj > 0 else cols - 1
    assert (i, j) in corners or (i, j) in midpoints or (i, j) == origin
    real_i = bi * rows + i
    real_j = bj * cols + j
    start_t = abs(real_i - rows // 2) + abs(real_j - cols // 2)
    end_t = start_t + cover_time[(i, j)]
    return (i, j), (start_t, end_t)

memo = {}
memo_complete = {}
USE_MEMO = True

def count_active(block, t):
    global memo, memo_complete, USE_MEMO
    b_start_pos, (start_t, end_t) = block_start_pos_times(*block)
    key = b_start_pos, (start_t, t)
    if t < start_t:
        return 0
    final_iter = t - start_t
    rel_parity = final_iter % 2
    complete = t >= end_t
    key_complete = b_start_pos, rel_parity
    if USE_MEMO:
        if complete and key_complete in memo_complete:
            return memo_complete[key_complete]
        elif key in memo:
            return memo[key]
    active_set = sum(fronts[b_start_pos][rel_parity:final_iter+1:2])
    if USE_MEMO:
        if complete:
            memo_complete[key_complete] = active_set
        else:
            memo[key] = active_set
    return active_set


sol = 0

# handle origin block
sol += count_active((0, 0), T)

# handle completed non-origin blocks (up to coordinate sum B-1)
for d in range(1, B):
    sol += count_active((d, 0), T)
    sol += count_active((-d, 0), T)
    sol += count_active((0, d), T)
    sol += count_active((0, -d), T)
    multiplier = (d - 1) * 4
    sol += count_active((d - 1, 1), T) * multiplier

# handle blocks of coord sum B and B+1, which are not entirely finished and won't be
# direction of entry might matter here
for d in [B, B+1]:
    sol += count_active((d, 0), T)
    sol += count_active((-d, 0), T)
    sol += count_active((0, d), T)
    sol += count_active((0, -d), T)
    multiplier = d - 1
    sol += count_active((d - 1, 1), T) * multiplier
    sol += count_active((-(d - 1), 1), T) * multiplier
    sol += count_active((d - 1, -1), T) * multiplier
    sol += count_active((-(d - 1), -1), T) * multiplier

print(sol)

