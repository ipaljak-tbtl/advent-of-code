lines = open("in", "r").readlines()

DIR = {"R": (0, 1), "D": (1, 0), "L": (0, -1), "U": (-1, 0)}


def parse():
    perimeter = 0
    coords = [(0, 0)]
    for line in lines:
        dir, len, _ = line.split()
        dir = DIR[dir]
        len = int(len)
        perimeter += len
        nxt = (coords[-1][0] + dir[0] * len, coords[-1][1] + dir[1] * len)
        coords.append(nxt)
    return coords, perimeter


coords, perimeter = parse()
sol = abs(sum((a[0] + b[0]) * (a[1] - b[1]) / 2 for (a, b) in zip(coords, coords[1:])))

print(sol + perimeter // 2 + 1)
