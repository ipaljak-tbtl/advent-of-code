import sys
import queue

poss = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        poss.append(tuple(map(int, line.strip().split(','))))

WIDTH = 71
HEIGHT = 71


lo = 0
hi = len(poss)

while lo < hi:
    mid = (lo + hi) // 2

    pos = poss[:mid]

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

    if (HEIGHT-1, WIDTH-1) in cost:
        lo = mid
    else:
        hi = mid-1

print(poss[lo])
