import sys
import itertools

puzzle = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        puzzle.append(line.strip())

n = len(puzzle)
m = len(puzzle[0])

def check_pair(x, y):
    if x == 'M' and y == 'S':
        return True
    if x == 'S' and y == 'M':
        return True
    return False

def check_part(part):
    if part[1][1] != 'A':
        return False
    return check_pair(part[0][0], part[2][2]) and check_pair(part[0][2], part[2][0])

sol = 0
for x, y in itertools.product(range(1, n-1), range(1, m-1)):
    if check_part([puzzle[x-i][y-1:y+2] for i in range(-1, 2)]):
        sol += 1

print(sol)

