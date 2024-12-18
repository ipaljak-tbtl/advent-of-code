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

    fences_x = [[-1 for _ in range(len(garden[0])+1)] \
            for _ in range(len(garden)+1)]
    fences_y = [[-1 for _ in range(len(garden[0])+1)] \
            for _ in range(len(garden)+1)]
    
    for x, y in new_visited:
        # upper
        new_x, new_y = x-1, y
        if outside(new_x, new_y):
            fences_x[x][y] = 0
        elif garden[x][y] != garden[new_x][new_y]:
            fences_x[x][y] = 0
        # lower
        new_x, new_y = x+1, y
        if outside(new_x, new_y):
            fences_x[x+1][y] = 1
        elif garden[x][y] != garden[new_x][new_y]:
            fences_x[x+1][y] = 1
        # left
        new_x, new_y = x, y-1
        if outside(new_x, new_y):
            fences_y[x][y] = 2
        elif garden[x][y] != garden[new_x][new_y]:
            fences_y[x][y] = 2
        # right
        new_x, new_y = x, y+1
        if outside(new_x, new_y):
            fences_y[x][y+1] = 3
        elif garden[x][y] != garden[new_x][new_y]:
            fences_y[x][y+1] = 3
    
    side = 0
    for x in range(len(fences_x)):
        y = 0

        on = -1
        while y < len(fences_x[0]):
            if fences_x[x][y] == -1:
                on = -1
            elif on != fences_x[x][y]:
                    side += 1
            on = fences_x[x][y]

            y += 1

    for y in range(len(fences_y)):
        x = 0

        on = False
        while x < len(fences_y[0]):
            if fences_y[x][y] == -1:
                on = -1
            elif on != fences_y[x][y]:
                    side += 1
            on = fences_y[x][y]

            x += 1

    return area * side

sol = 0
for i in range(len(garden)):
    for j in range(len(garden[0])):
        sol += bfs(i, j)

print(sol)
