import sys

puzzle = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        puzzle.append(line.strip())

x = 0
y = 0
d = 0
for i in range(len(puzzle)):
    if (ind := puzzle[i].find('^')) != -1:
        x = i
        y = ind
        d = 0
        puzzle[i].replace("^", ".")
        break

if x == 0 and y == 0:
    print("Guard not found")

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]
def move_guard(puzzle, guard):
    x, y, d = guard

    new_x = x + dx[d]
    new_y = y + dy[d]

    if new_x < 0 or new_x >= len(puzzle) or new_y < 0 or new_y >= len(puzzle[0]):
        return None

    if puzzle[new_x][new_y] == '#':
        d = (d + 1) % 4
        return x, y, d
    
    return new_x, new_y, d

all_positions = set()

while True:
    all_positions.add((x, y))
    new_guard = move_guard(puzzle, (x, y, d))

    if new_guard == None:
        break

    x, y, d = new_guard

print(len(all_positions))
