import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

sol = 0

for line in lines:
    line = line.strip()

    maxx = -1
    r = 0
    for x in reversed(line):
        x = int(x)
        if maxx == -1:
            maxx = x
            continue

        r = max(r, x * 10 + maxx)
        maxx = max(maxx, x)

    sol += r

print(sol)

