#!/usr/bin/env python3

import sys
from collections import defaultdict
from queue import PriorityQueue as PQ

LOG = False
def log(*args, **kw):
    if LOG:
        print(*args, **kw)

delta = {
    'n': (-1, 0),
    's': (1, 0),
    'w': (0, -1),
    'e': (0, 1)
}

opp = {
    'n': 's',
    's': 'n',
    'w': 'e',
    'e': 'w'
}

losses = [[int(c) for c in line.strip()] for line in sys.stdin]
rows = len(losses)
cols = len(losses[0])

def next_iter(loss, count, d, pos):
    for next_d in 'nswe':
        if d and next_d == opp[d]:
            continue
        if d and next_d == d and count >= 3:
            continue
        i, j = pos
        di, dj = delta[next_d]
        n_i, n_j = i + di, j + dj
        n_count = count + 1 if next_d == d else 1
        if not (n_i in range(rows) and n_j in range(cols)):
            continue
        n_loss = loss + losses[n_i][n_j]
        yield n_loss, n_count, next_d, (n_i, n_j)

start = (0, 0, None, (0, 0))
end_pos = (rows - 1, cols - 1)
current_best = {((0, 0), d, 0): 0 for d in 'nswe'}
path = {((0, 0), None, 0): [((0, 0), None)]}
q = PQ()
q.put(start)

def print_grid(pos, d, count):
    cur_path = path[(pos, d, count)]
    cur_path = dict(cur_path)

    syms = {'n': '^', 's': 'v', 'w': '<', 'e': '>'}
    CRED = '\33[91m'
    CEND = '\33[0m'

    print('-'*80)
    for i, row in enumerate(losses):
        for j, loss in enumerate(row):
            sym = loss
            if (i, j) in cur_path:
                d = cur_path[(i, j)] 
                if d in syms:
                    sym = CRED + syms[d] + CEND
            if (i, j) == pos:
                sym = CRED + '*' + CEND
            print(sym, end='')
        print()
    print('-'*80)


while not q.empty():
    loss, count, d, pos = q.get()
    log(f'Processing {pos} coming in {d}, count {count}: loss {loss}')
    if pos == end_pos:
        continue
    state = (pos, d, count)
    for n_loss, n_count, n_d, n_pos in next_iter(loss, count, d, pos):
        n_state = (n_pos, n_d, n_count)
        if n_state not in current_best or n_loss < current_best[n_state]:
            current_best[n_state] = n_loss
            path[n_state] = path[state] + [(n_pos, n_d)]
            q.put((n_loss, n_count, n_d, n_pos))
            if LOG: print_grid(*n_state)
            log(f'New best for {n_pos} coming in {n_d}, count {count}: loss {n_loss}')
            log()
        else:
            log(f'No improvement: {n_pos} coming in {n_d}, count {count}: loss {n_loss}')

sol = None
for d in 'se':
    for count in range(3+1):
        state = (end_pos, d, count)
        if state in current_best:
            l = current_best[state]
            if sol is None or l < sol:
                sol = l
                print_grid(*state)
                print('New best!') 
                print()

print(sol)

