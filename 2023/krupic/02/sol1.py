#!/usr/bin/env python3

import sys

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
    return lower_bounds['red'] <= 12 and lower_bounds['green'] <= 13 and lower_bounds['blue'] <= 14

sol = 0

for line in map(str.rstrip, sys.stdin):
    game, rounds = parse_game(line)
    if solve_game(rounds):
        print(game)
        sol += game
print(sol)


