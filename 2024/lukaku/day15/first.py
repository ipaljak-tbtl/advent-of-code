import sys
import queue

house = []
moves = ""

with open(sys.argv[1], 'r') as file:
    for line in file:
        line = line.strip()

        if len(line) == 0:
            break

        house.append(list(line))

    for line in file:
        moves += line.strip()


robot = None
for i in range(len(house)):
    for j in range(len(house[0])):
        if house[i][j] == '@':
            robot = i, j
            house[i][j] = '.'

dpos = {'<': (0, -1), '>': (0, 1), '^': (-1, 0), 'v': (1, 0)}

        
for move in moves:
    d = dpos[move]
    start_x, start_y = robot[0] + d[0], robot[1] + d[1]

    end_x, end_y = start_x, start_y

    while house[end_x][end_y] == 'O':
        end_x, end_y = end_x + d[0], end_y + d[1]

    if house[end_x][end_y] == '#':
        continue

    house[end_x][end_y] = 'O'
    house[start_x][start_y] = '.'
    robot = start_x, start_y

sol = 0
for i in range(len(house)):
    for j in range(len(house[0])):
        if house[i][j] == 'O':
            sol += 100 * i  + j

print(sol)
    
