import sys

from queue import Queue

trail = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        trail.append(line.strip())

def bfs(x, y, trail):
    queue = Queue()
    queue.put((x, y))

    visited = set()
    visited.add((x, y))
    rating = dict()
    rating[(x, y)] = 1

    trail_ends = []

    while queue.empty() == False:
        x, y = queue.get()

        dxs = [-1, 0, 1, 0]
        dys = [0, -1, 0, 1]

        if trail[x][y] == '9':
            trail_ends.append((x, y))

        for dx, dy in zip(dxs, dys):
            new_x = x + dx
            new_y = y + dy

            if new_x < 0 or new_x >= len(trail):
                continue
            if new_y < 0 or new_y >= len(trail[0]):
                continue
            if int(trail[new_x][new_y]) - int(trail[x][y]) != 1:
                continue

            r = rating.get((new_x, new_y), 0)
            r += rating.get((x, y))

            rating[(new_x, new_y)] = r

            if (new_x, new_y) in visited:
                continue

            queue.put((new_x, new_y))
            visited.add((new_x, new_y))

    return sum(rating[(x, y)] for x, y in trail_ends)
    
sol = 0
for x in range(len(trail)):
    for y in range(len(trail[0])):
        if trail[x][y] == '0':
            sol += bfs(x, y, trail)

print(sol)

