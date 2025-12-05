import sys

with open(sys.argv[1], 'r') as f:
    lines = list(map(str.strip, f.readlines()))

ranges = []
ingredients = []
for line in lines:
    line = line.strip()

    if '-' in line:
        ranges.append(list(map(int, line.split('-'))))
    elif len(line) > 0:
        ingredients.append(int(line))

def fresh(ranges, x):
    for l, r in ranges:
        if l <= x and x <= r:
            return True
    return False

sol = 0
for x in ingredients:
    if fresh(ranges, x):
        sol += 1

print(sol)
