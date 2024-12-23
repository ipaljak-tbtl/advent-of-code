import sys
import queue

house = []
moves = ""

with open(sys.argv[1], 'r') as file:
    for line in file:
        line = line.strip()

        if len(line) == 0:
            break

        house.append(list(line.replace("#", "##").replace(".", "..").replace("@", "@.").replace("O", "[]")))

    for line in file:
        moves += line.strip()


robot = None
for i in range(len(house)):
    for j in range(len(house[0])):
        if house[i][j] == '@':
            robot = i, j
            house[i][j] = '.'

dpos = {'<': (0, -1), '>': (0, 1), '^': (-1, 0), 'v': (1, 0)}

visited = set()

def bfs(start_x, start_y, d):
    q = queue.Queue()
    visited.add((start_x, start_y))
    q.put((start_x, start_y))

    while q.empty() == False:
        x, y = q.get()

        new_x, new_y = x + d[0], y + d[1]

        if (new_x, new_y) in visited:
            continue

        if house[new_x][new_y] == '#':
            return False
        if house[new_x][new_y] == '.':
            continue
        if house[new_x][new_y] == '[':
            q.put((new_x, new_y))
            visited.add((new_x, new_y))
            q.put((new_x, new_y+1))
            visited.add((new_x, new_y+1))
        if house[new_x][new_y] == ']':
            q.put((new_x, new_y))
            visited.add((new_x, new_y))
            q.put((new_x, new_y-1))
            visited.add((new_x, new_y-1))

    return True

def move_visited(d):
    new_positions = set()

    for x, y in visited:
        if house[x][y] == ']':
            continue
        new_positions.add((x + d[0], y + d[1]))

    for x, y in visited:
        house[x][y] = '.'

    for x, y in new_positions:
        house[x][y] = '['
        house[x][y+1] = ']'

        
for move in moves:
    d = dpos[move]
    start_x, start_y = robot[0] + d[0], robot[1] + d[1]

    if house[start_x][start_y] == '#':
        continue
    if house[start_x][start_y] == '.':
        robot = start_x, start_y
        continue

    visited = set()
    if house[start_x][start_y] == '[':
        if bfs(start_x, start_y, d) and bfs(start_x, start_y+1, d):
            move_visited(d)
            robot = start_x, start_y
    if house[start_x][start_y] == ']':
        if bfs(start_x, start_y, d) and bfs(start_x, start_y-1, d):
            move_visited(d)
            robot = start_x, start_y

sol = 0
for i in range(len(house)):
    for j in range(len(house[0])):
        if house[i][j] == '[':
            sol += 100 * i  + j

print(sol)
    
