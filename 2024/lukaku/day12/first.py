import sys
from queue import Queue

garden = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        garden.append(line.strip())

visited = set()

def bfs(x, y):
    if (x, y) in visited:
        return 0

    new_visited = set()

    queue = Queue()
    queue.put((x, y))
    new_visited.add((x, y))
    visited.add((x, y))

    dxs = [-1, 0, 1, 0]
    dys = [0, -1, 0, 1]

    def outside(a, b):
        return a < 0 or b < 0 or a >= len(garden) or b >= len(garden[0])

    while queue.empty() == False:
        x, y = queue.get()

        for dx, dy in zip(dxs, dys):
            new_x = x + dx
            new_y = y + dy

            if outside(new_x, new_y):
                continue
            if (new_x, new_y) in visited:
                continue
            if garden[new_x][new_y] != garden[x][y]:
                continue

            queue.put((new_x, new_y))
            visited.add((new_x, new_y))
            new_visited.add((new_x, new_y))

    area = len(new_visited)

    perimeter = 0
    for x, y in new_visited:
        for dx, dy in zip(dxs, dys):
            new_x = x + dx
            new_y = y + dy

            if outside(new_x, new_y):
                perimeter += 1
                continue
            if garden[x][y] != garden[new_x][new_y]:
                perimeter += 1

    return area * perimeter

sol = 0
for i in range(len(garden)):
    for j in range(len(garden[0])):
        sol += bfs(i, j)

print(sol)
