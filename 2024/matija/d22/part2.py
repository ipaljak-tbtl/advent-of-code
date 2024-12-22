#!/usr/bin/env python3

from collections import deque
from itertools import product
import sys

MOD = 16777216


def next_secret_number(secret_number):
    secret_number = (secret_number ^ (secret_number * 64)) % MOD
    secret_number = (secret_number ^ (secret_number // 32)) % MOD
    secret_number = (secret_number ^ (secret_number * 2048)) % MOD
    return secret_number


all_seqs = []
for line in sys.stdin:
    secret_number = int(line.strip())

    last_price = secret_number % 10
    diffs = deque(maxlen=4)
    all_seqs.append({})

    for _ in range(2000):
        secret_number = next_secret_number(secret_number)
        price = secret_number % 10
        diffs.append(price - last_price)
        last_price = price

        seq = tuple(diffs)
        if seq not in all_seqs[-1]:
            all_seqs[-1][seq] = price

max_price = 0
for seq in product(range(-9, 10), repeat=4):
    max_price = max(max_price, sum(seqs.get(seq, 0) for seqs in all_seqs))

print(max_price)
