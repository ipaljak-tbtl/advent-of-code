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


ranges = sorted(ranges, key = lambda x: (x[0], x[1]))
while True:
    ranges2 = []

    it = 0
    l1, r1 = ranges[it]
    it += 1
    while it < len(ranges):
        l2, r2 = ranges[it]
        it += 1
        if r1 < l2:
            ranges2.append((l1, r1))
            l1, r1 = l2, r2
            continue

        r1 = max(r1, r2)

    ranges2.append((l1, r1))

    if len(ranges) == len(ranges2):
        break
    ranges = sorted(ranges2, key = lambda x: (x[0], x[1]))

sol = 0
for l, r in ranges:
    sol += r-l+1

print(sol)
