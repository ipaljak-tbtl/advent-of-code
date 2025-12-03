import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

sol = 0

for line in lines:
    line = line.strip()
    r = 0
    line = list(map(int, list(line)))
    for i in range(-11, 1):
        if i != 0:
            maxx = max(line[:i])
        else:
            maxx = max(line)
        ind = line.index(maxx)

        r = r * 10 + maxx
        line = line[ind+1:]
    sol += r

print(sol)

