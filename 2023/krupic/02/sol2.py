#!/usr/bin/env python3

import sys
from functools import reduce

def parse_game(line):
    game, rounds = line.split(':', maxsplit=1)
    game = int(game.split()[1])
    rounds = map(parse_round, rounds.split(';'))
    return game, rounds

def parse_round(round):
    return {color: int(count) for count, color in map(lambda r: r.strip().split(), round.split(','))}

def solve_game(rounds):
    lower_bounds = {'red': 0, 'green': 0, 'blue': 0}
    for round in rounds:
        for color, count in round.items():
            lower_bounds[color] = max(lower_bounds[color], count)
    print(lower_bounds)
    power = reduce(int.__mul__, lower_bounds.values())
    print(power)
    return power

sol = 0

for line in map(str.rstrip, sys.stdin):
    game, rounds = parse_game(line)
    sol += solve_game(rounds)
print(sol)


