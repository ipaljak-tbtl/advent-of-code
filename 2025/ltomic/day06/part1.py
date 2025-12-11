import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

for i in range(len(lines)):
    lines[i] = lines[i][:-1]

ops = lines[-1].split()

lines = lines[:-1]

for i in range(len(lines)):
    lines[i] = list(map(int, lines[i].split()))

sol = 0
for i in range(len(lines[0])):
    nums = [x[i] for x in lines]

    if ops[i] == '+':
        sol += sum(nums)
    else:
        sol += math.prod(nums)

print(sol)
