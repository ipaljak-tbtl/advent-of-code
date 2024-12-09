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

for file_id in reversed(range(len(files_size))):
    file_size = files_size[file_id]

    try:
        free_gap = next(i for i in range(len(gaps_size)) if gaps_size[i] >= file_size)
        if gaps_start[free_gap] >= files_start[file_id]:
            # do not move to the right
            continue
        #print(f'move file {file_id} (size {file_size}) from {files_start[file_id]} to gap at {gaps_start[free_gap]} (size {gaps_size[free_gap]})')
        files_start[file_id] = gaps_start[free_gap]

        gaps_start[free_gap] += file_size
        gaps_size[free_gap] -= file_size
    except StopIteration:
        pass

sol = 0
for file_id, (start, size) in enumerate(zip(files_start, files_size)):
    #print(f'file {file_id} of size {size} at {start}')
    sol += file_id * sum(start + i for i in range(size))

print(sol)

