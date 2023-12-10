#!/usr/bin/env python3

import sys

def parse_line(line):
    card, nums = line.split(':')
    winning, numbers = map(lambda s: map(int, s.strip().split()), nums.split('|'))
    return set(winning), numbers

total_cards = 0

extra_cards = dict()

for card, line in enumerate(map(str.rstrip, sys.stdin)):
    card += 1
    winning, numbers = parse_line(line)

    multiplier = 1 + (extra_cards.get(card) or 0)
    total_cards += multiplier

    score = sum(1 for x in numbers if x in winning)
    for c in range(card+1, card+1+score):
        if c not in extra_cards:
            extra_cards[c] = multiplier
        else:
            extra_cards[c] += multiplier

print(total_cards)

