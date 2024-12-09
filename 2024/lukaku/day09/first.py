import sys

with open(sys.argv[1], 'r') as file:
    puzzle = file.readlines()[0].strip()

disk_map = []

curr_id = 0
empty = False
sum_x = 0
for x in puzzle:
    x = int(x)
    if empty == False:
        disk_map += [curr_id] * x
        empty = True
        curr_id += 1
        sum_x += x
    else:
        disk_map += [-1] * x
        empty = False

i = 0
while i < sum_x:
    if disk_map[i] != -1:
        i += 1
        continue
    while disk_map[-1] == -1:
        disk_map.pop()
    disk_map[i] = disk_map[-1]
    disk_map.pop()
    i += 1


sol = 0
for i in range(sum_x):
    sol += i * disk_map[i]

print(sol)
