import sys

puzzle = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        puzzle.append(list(line.strip()))

x = -1
y = -1
d = 0
for i in range(len(puzzle)):
    if x != -1:
        break
    for j in range(len(puzzle[i])):
        if puzzle[i][j] == '^':
            x = i
            y = j
            d = 0
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


start_x = x
start_y = y
start_d = d
cnt = 0

for i in range(len(puzzle)):
    for j in range(len(puzzle[0])):
        print(i, j)

        if (i, j) == (start_x, start_y):
            continue
        if puzzle[i][j] == '#':
            continue
        
        puzzle[i][j] = '#'
        x = start_x
        y = start_y
        d = start_d

        all_positions = set()

        while True:
            if (x, y, d) in all_positions:
                cnt += 1
                break

            all_positions.add((x, y, d))
            new_guard = move_guard(puzzle, (x, y, d))

            if new_guard == None:
                break

            x, y, d = new_guard

        puzzle[i][j] = '.'

print(cnt)
