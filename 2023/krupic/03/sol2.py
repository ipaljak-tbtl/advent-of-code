#!/usr/bin/env python3

import sys
import re

number = re.compile(r'\d+')
gear = re.compile(r'\*')

def parse_line(line):
    numbers = list(number.finditer(line))
    gears = gear.finditer(line)
    return numbers, gears

def adj_part_numbers(gear, adj_line_nums):
    col = gear.start()
    nums = []
    for num in adj_line_nums:
        start, end = num.span()
        if start - 1 <= col <= end:
            print(f'{num.group()} {(start,end)} is next to gear ({col})')
            nums.append(int(num.group()))
    return nums

def solve_line(cur_line_gears, prev_line_nums, cur_line_nums, next_line_nums):
    nums = prev_line_nums + cur_line_nums + next_line_nums
    ratio_sum = 0
    for gear in cur_line_gears:
        adj_nums = adj_part_numbers(gear, nums)
        if len(adj_nums) != 2:
            print(f'Not actually a gear ({len(adj_nums)} adj)')
            continue
        x, y = adj_nums
        print(f'{x} * {y} = {x*y}')
        ratio_sum += x * y 
    print(ratio_sum)
    return ratio_sum

prev_line_nums = []
cur_line_nums = []
next_line_nums = []

cur_line_gears = []

sol = 0

for i, next_line in enumerate(map(str.rstrip, sys.stdin)):
    print(f'Solving line {i - 1}, parsing line {i}')
    next_line_nums, next_line_gears = parse_line(next_line)
    sol += solve_line(
        cur_line_gears,
        prev_line_nums,
        cur_line_nums,
        next_line_nums
    )
    
    prev_line_nums = cur_line_nums
    cur_line_nums = next_line_nums
    cur_line_gears = next_line_gears

print(f'Solving last line')
sol += solve_line(
    cur_line_gears,
    prev_line_nums,
    cur_line_nums,
    next_line_nums
)
print(sol)

