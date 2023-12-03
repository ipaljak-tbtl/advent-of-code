#!/usr/bin/env python3

import sys
import re

number = re.compile(r'\d+')
symbol = re.compile(r'[^\d.]')

def parse_line(line):
    numbers = number.finditer(line)
    symbols = list(symbol.finditer(line))
    return numbers, symbols

def is_part_number(number, adj_line_syms):
    start, end = number.span()
    for sym in adj_line_syms:
        if start - 1 <= sym.start() <= end:
            print(f'{number.group()} {(start,end)} is next to {sym.group()} ({sym.start()})')
            return True
    return False

def solve_line(cur_line_nums, prev_line_syms, cur_line_syms, next_line_syms):
    syms = prev_line_syms + cur_line_syms + next_line_syms
    return [int(num.group()) for num in cur_line_nums if is_part_number(num, syms)]

prev_line_syms = []
cur_line_syms = []
next_line_syms = []

cur_line_nums = []

part_nums = []

for i, next_line in enumerate(map(str.rstrip, sys.stdin)):
    print(f'Solving line {i - 1}, parsing line {i}')
    next_line_nums, next_line_syms = parse_line(next_line)
    part_nums += solve_line(
        cur_line_nums,
        prev_line_syms,
        cur_line_syms,
        next_line_syms
    )
    
    prev_line_syms = cur_line_syms
    cur_line_syms = next_line_syms
    cur_line_nums = next_line_nums

print(f'Solving last line')
part_nums += solve_line(
    cur_line_nums,
    prev_line_syms,
    cur_line_syms,
    next_line_syms
)
print(sum(part_nums))

