#!/usr/bin/env python3

import sys

line = list(map(int, input().strip()))
start_pos = [0]
for x in line[:-1]:
    start_pos.append(start_pos[-1] + x)

files_size, gaps_size = line[::2], line[1::2]
files_start, gaps_start = start_pos[::2], start_pos[1::2]
#print(list(zip(files_start, files_size)))
#print(list(zip(gaps_start, gaps_size)))

disk = []
file_id = 0
for i in range(len(line)):
    if i % 2 == 0:
        disk += [file_id] * line[i]
        file_id += 1
    else:
        disk += [None] * line[i]
#print(disk)

def find_free(start):
    return next(i for i in range(start, len(disk)) if disk[i] is None)

def find_file(start):
    return next(i for i in range(start, -1, -1) if disk[i] is not None)

free_ptr = find_free(0)
file_ptr = find_file(len(disk) - 1)

while free_ptr < file_ptr:
    disk[free_ptr] = disk[file_ptr]
    disk[file_ptr] = None
    try:
        free_ptr = find_free(free_ptr + 1)
        file_ptr = find_file(file_ptr - 1)
    except StopIteration:
        break

#print(disk)

sol = sum(block * i for i, block in enumerate(disk) if block is not None)
print(sol)

