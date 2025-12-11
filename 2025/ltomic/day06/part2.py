import sys
import math

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

for i in range(len(lines)):
    lines[i] = lines[i][:-1]

ops = lines[-1].split()
nums = []
sol = 0
for j in range(len(lines[0])):
    curr = 0
    for i in range(len(lines[:-1])):
        if lines[i][j] != ' ':
            curr = curr * 10 + int(lines[i][j])
    if curr != 0:
        nums.append(curr)
    else:
        if ops[0] == '+':
            sol += sum(nums)
        else:
            sol += math.prod(nums)
        ops = ops[1:]
        nums = []

if ops[0] == '+':
    sol += sum(nums)
else:
    sol += math.prod(nums)

print(sol)
