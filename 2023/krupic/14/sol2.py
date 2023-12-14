#!/usr/bin/env python3

import sys
from itertools import chain
from operator import itemgetter
from collections import defaultdict

grid = list(map(str.rstrip, sys.stdin))
rows = len(grid)
cols = len(grid[0])
obstacles_h = [[j for j, tile in enumerate(row) if tile == '#'] for row in grid]
obstacles_v = [[i for i, tile in enumerate(col) if tile == '#'] for col in zip(*grid)]
rocks_by_col = [[i for i, tile in enumerate(col) if tile == 'O'] for col in zip(*grid)]

def simulate_step(rocks_by_line, d):
    new_rocks_by_line = []
    rev = d in 'se'
    vertical = d in 'ns'
    obstacles_by_line = obstacles_v if vertical else obstacles_h
    for rocks, obstacles in zip(rocks_by_line, obstacles_by_line):
        lowest_empty = 0 if not rev else (rows if vertical else cols) - 1
        delta = 1 if not rev else -1
        it = sorted(
            chain(
                map(lambda r: (r, 'O'), rocks),
                map(lambda o: (o, '#'), obstacles)
            ),
            key=itemgetter(0),
            reverse=rev
        )
        new_rocks = []
        for i, tile in it:
            if tile == 'O':
                new_rocks.append(lowest_empty)
                lowest_empty += delta
            elif tile == '#':
                lowest_empty = i + delta
        new_rocks_by_line.append(new_rocks)
    return new_rocks_by_line 

def transpose(rocks_by_line, max_idx):
    rocks_t = defaultdict(list)
    for major, line in enumerate(rocks_by_line):
        for minor in line:
            rocks_t[minor].append(major)
    return [rocks_t[minor] for minor in range(max_idx)]

visited_states = dict()
cycle_state = None

def simulate_round(step):
    global last_state
    global rocks_by_col
    global cycle_state
    rocks_by_row = transpose(simulate_step(rocks_by_col, 'n'), rows)         
    rocks_by_col = transpose(simulate_step(rocks_by_row, 'w'), cols)         
    rocks_by_row = transpose(simulate_step(rocks_by_col, 's'), rows)         
    rocks_by_col = transpose(simulate_step(rocks_by_row, 'e'), cols)         
    new_state = frozenset((i,j) for j, col in enumerate(rocks_by_col) for i in col)
    if new_state in visited_states:
        cycle_state = new_state
        return False
    else:
        visited_states[new_state] = step
        return True

STEPS = 1000000000
final_state = None
for step in range(STEPS):
    if step % 1000 == 0:
        print(f'Step {step}')
    if not simulate_round(step):
        print(f'Cycle reached at step {step}, last visited at step {visited_states[cycle_state]}')
        cycle_len = step - visited_states[cycle_state]
        print(f'Cycle len {cycle_len}')
        remaining = (STEPS - 1 - step) % cycle_len
        final_state_step = visited_states[cycle_state] + remaining
        final_state = next(k for k, v in visited_states.items() if v == final_state_step)
        break

sol = sum(rows - i for i, _ in final_state)
print(sol)

