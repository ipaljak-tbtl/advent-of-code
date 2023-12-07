#!/usr/bin/env python3

import sys
from operator import eq, lt, gt
from collections import Counter

LABELS = 'J23456789TQKA'
def lex_hand_key(hand):
    return list(map(LABELS.index, hand))

def best_hand_type_key(hand):
    counts = Counter(hand)
    jokers = counts['J']
    del counts['J']
    if counts:
        k = counts.most_common()[0][0]
        counts[k] += jokers
        return hand_type_key(counts)
    else:
        return [jokers]

def hand_type_key(hand):
    return [v for c, v in Counter(hand).most_common()]

def hand_key(hand):
    return (best_hand_type_key(hand), lex_hand_key(hand))

def parse_line(line):
    hand, bid = line.split()
    return hand, int(bid)

hands = sorted([parse_line(line) for line in sys.stdin], key=lambda h: hand_key(h[0]))

sol = 0
for i, (hand, bid) in enumerate(hands):
    print(i+1, hand, bid)
    print(hand_key(hand))
    sol += (i+1) * bid
print(sol)

