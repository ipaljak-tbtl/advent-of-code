import sys

with open(sys.argv[1], 'r') as file:
    lines = file.readlines()
    towels = list(map(str.strip, lines[0].split(',')))

    designs = list(map(str.strip, lines[2:]))

INF = 1e18

def dp(design):
    if len(design) == 0:
        return 1
    if design in mem:
        return mem[design]

    mem[design] = 0
    for towel in towels:
        if towel != design[:len(towel)]:
            continue
        mem[design] += dp(design[len(towel):])

    return mem[design]

cnt = 0
for design in designs:
    mem = dict()
    cnt += dp(design)

print(cnt)
