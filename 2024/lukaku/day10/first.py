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

    cnt = 0

    while queue.empty() == False:
        x, y = queue.get()

        if trail[x][y] == '9':
            cnt += 1

        dxs = [-1, 0, 1, 0]
        dys = [0, -1, 0, 1]

        for dx, dy in zip(dxs, dys):
            new_x = x + dx
            new_y = y + dy

            if new_x < 0 or new_x >= len(trail):
                continue
            if new_y < 0 or new_y >= len(trail[0]):
                continue
            if int(trail[new_x][new_y]) - int(trail[x][y]) != 1:
                continue
            if (new_x, new_y) in visited:
                continue

            queue.put((new_x, new_y))
            visited.add((new_x, new_y))

    return cnt

sol = 0
for x in range(len(trail)):
    for y in range(len(trail[0])):
        if trail[x][y] == '0':
            sol += bfs(x, y, trail)

print(sol)

