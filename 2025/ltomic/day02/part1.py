import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

ranges = lines[0].split(',')

ranges = [list(map(int, i.split('-'))) for i in ranges]

def invalid(x):
    x = str(x)

    if len(x) % 2 == 1:
        return False

    return x[:len(x)//2] == x[len(x)//2:]

sol = 0
for a, b in ranges:
    for x in range(a, b+1):
        if invalid(x):
            sol += x

print(sol)
