import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

state = 50
sol = 0
for line in lines:
    line = line.strip()
    d = -1 if line[0] == 'L' else 1
    n = int(line[1:])

    state += d * n

    state %= 100

    if state == 0:
        sol += 1

print(sol)
