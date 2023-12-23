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
    for brick in bricks:
        new_z = 1
        for other in bricks:
            if other.B[2] >= brick.A[2]:
                continue
            if brick.collides(other):
                new_z = max(new_z, other.B[2] + 1)

        brick.fall(brick.A[2] - new_z)

    return bricks


bricks = sorted([Brick(line) for line in lines], key=lambda brick: brick.B[2])
bricks = sorted(fall(bricks), key=lambda brick: brick.B[2])

sol = 0
for brick in tqdm(bricks):
    others = bricks.copy()
    others.remove(brick)
    fallen_others = sorted(fall(deepcopy(others)), key=lambda brick: brick.B[2])
    sol += others == fallen_others


print(sol)
