import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

state = 50
sol = 0
for line in lines:
    line = line.strip()
    d = -1 if line[0] == 'L' else 1
    n = int(line[1:])

    sol += n // 100
    n %= 100

    new_state = state + d * n

    if state > 0 and new_state <= 0:
        sol += 1
    if new_state >= 100:
        sol += 1

    state = new_state % 100

print(sol)
