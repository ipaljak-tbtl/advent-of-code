from copy import *
from tqdm import tqdm

lines = open("in", "r").readlines()


class Brick:
    def __init__(self, line):
        tokens = line.split("~")
        self.A = list(map(int, tokens[0].split(",")))
        self.B = list(map(int, tokens[1].split(",")))

    def fall(self, step):
        self.A[2] -= step
        self.B[2] -= step

    def collides(self, other):
        return (
            self.A[0] <= other.B[0]
            and other.A[0] <= self.B[0]
            and self.A[1] <= other.B[1]
            and other.A[1] <= self.B[1]
        )

    def __eq__(self, other):
        return self.A == other.A and self.B == other.B


def fall(bricks):
    cnt = 0
    for brick in bricks:
        new_z = 1
        for other in bricks:
            if other.B[2] >= brick.A[2]:
                continue
            if brick.collides(other):
                new_z = max(new_z, other.B[2] + 1)

        cnt += (brick.A[2] - new_z) > 0
        brick.fall(brick.A[2] - new_z)

    return bricks, cnt


bricks = sorted([Brick(line) for line in lines], key=lambda brick: brick.B[2])
bricks = sorted(fall(bricks)[0], key=lambda brick: brick.B[2])

sol = 0
for brick in tqdm(bricks):
    others = bricks.copy()
    others.remove(brick)
    _, cnt = fall(deepcopy(others))
    sol += cnt


print(sol)
