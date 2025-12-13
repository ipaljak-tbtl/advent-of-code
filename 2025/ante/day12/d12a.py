#!/usr/bin/env python3
 
import sys

from ortools.sat.python import cp_model

NTILES = 6

def convert(tile):
    T = set()
    for i in range(3):
        for j in range(3):
            if tile[i][j] == '#':
                T.add((i, j))
    return T


def flip(tile):
    T = set()
    for (i, j) in tile:
        T.add((i, 2 - j))
    return T


def rotate(tile):
    T = set()
    for (i, j) in tile:
        T.add((j, 2 - i))
    return T


def move(tile, x, y):
    T = set()
    for (i, j) in tile:
        T.add((i + x, j + y))
    return T


def solve_or(tiles, counts, m, n):
    print("Solving for", m, n, counts, tiles)

    total = 0
    for i in range(NTILES):
        total += counts[i]*len(tiles[i])
    if total > m*n:
        return False

    T = []
    for i, t in enumerate(tiles):
        T.append(set())
        for x in range(m - 2):
            for y in range(n - 2):
                for _ in range(2):
                    for _ in range(4):
                        T[i].add(frozenset(move(t, x, y)))
                        t = rotate(t)
                    t = flip(t)

    print("Building model...")
    model = cp_model.CpModel()
    
    xl = [[model.NewBoolVar(f'x_{i}_{j}') for j in range(len(T[i]))] for i in range(NTILES)]
    for i in range(NTILES):
        model.add(sum([xl[i][j] for j in range(len(T[i]))]) == counts[i])

    for x in range(m):
        for y in range(n):
            tile_indices = []
            for i in range(NTILES):
                for j, u in enumerate(T[i]):    
                    if (x, y) in u:
                        tile_indices.append((i, j))
            if tile_indices:
                model.AddAtMostOne([xl[i][j] for i, j in tile_indices])

    print("Checking...")
    solver = cp_model.CpSolver()
    solver.parameters.num_search_workers = 24
    status = solver.Solve(model)

    if status not in (cp_model.OPTIMAL, cp_model.FEASIBLE):
        return False
    
    return True

def less(a, b):
    for x, y in zip(a, b):
        if x > y:
            return False
    return True


def check_trivial(all, current):
    for key, value in all.items():
        if less(key, current) and not value:
            print("Trivial false:", key, current)
            return False
        if less(current, key) and value:
            print("Trivial true:", key, current)
            return True
    return None
        

if __name__ == "__main__":
    total = 0
    lines = sys.stdin.readlines()
    tiles = [convert(lines[5*i+1:5*i+4]) for i in range(NTILES)]
    print(tiles)
    case = 0
    all = {}
    for line in lines[30:]:
        case += 1   
        items = line.split()
        counts = list(map(int, items[1:]))
        m, n = map(int, items[0][:-1].split('x'))
        current = tuple(counts + [-m, -n])
        trivial = check_trivial(all, current)
        if trivial is not None:
            if trivial:
                print("Case", case, "YES")
                total += 1
            else:
                print("Case", case, "NO")
            continue
        if solve_or(tiles, counts, m, n):
            print("Case", case, "YES")
            total += 1
            all[current] = True
        else:
            print("Case", case, "NO")
            all[current] = False
    
    print(total)