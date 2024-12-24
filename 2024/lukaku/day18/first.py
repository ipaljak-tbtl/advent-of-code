import sys
import queue

pos = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        pos.append(tuple(map(int, line.strip().split(','))))

WIDTH = 71
HEIGHT = 71

pos = pos[:1024]
pos = set(pos)
q = queue.Queue()
cost = dict()
q.put((0, 0))
cost[0, 0] = 0

while q.empty() == False:
    x, y = q.get()

    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        new_x, new_y = x + dx, y + dy

        if new_x < 0 or new_x >= HEIGHT:
            continue
        if new_y < 0 or new_y >= WIDTH:
            continue
        if (new_x, new_y) in cost:
            continue
        if (new_y, new_x) in pos:
            continue

        cost[new_x, new_y] = cost[x, y] + 1
        q.put((new_x, new_y))

print(cost[HEIGHT-1, WIDTH-1])
