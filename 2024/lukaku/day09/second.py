import sys

with open(sys.argv[1], 'r') as file:
    puzzle = file.readlines()[0].strip()

disk_map = []

curr_id = 0
empty = 0
total_x = 0
for x in puzzle:
    x = int(x)
    
    if empty == False:
        disk_map.append([total_x, x, curr_id])
        curr_id += 1

    empty ^= 1

    total_x += x

tried = set()

i = -1
while -i <= len(disk_map):
    disk_file = disk_map[i]
    if disk_file[2] in tried:
        i -= 1
        continue
    tried.add(disk_file[2])

    for j in range(len(disk_map)-1):
        if disk_map[j][0] >= disk_file[0]:
            i -= 1
            break

        if disk_map[j+1][0] - disk_map[j][0] - disk_map[j][1] >= disk_file[1]:
            disk_map[i][0] = disk_map[j][0] + disk_map[j][1]

            disk_map = sorted(disk_map, key = lambda x: x[0])
            i = -1
            break


sol = 0
for a, b, x in disk_map:
    for i in range(a, a+b):
        sol += i * x

print(sol)
