#!/usr/bin/env python3

import sys

MOD = 16777216


def next_secret_number(secret_number):
    secret_number = (secret_number ^ (secret_number * 64)) % MOD
    secret_number = (secret_number ^ (secret_number // 32)) % MOD
    secret_number = (secret_number ^ (secret_number * 2048)) % MOD
    return secret_number


total = 0
for line in sys.stdin:
    secret_number = int(line.strip())
    for _ in range(2000):
        secret_number = next_secret_number(secret_number)
    total += secret_number

print(total)
