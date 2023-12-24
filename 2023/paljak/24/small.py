import itertools

lines = open("in", "r").readlines()
TEST_LO, TEST_HI = 200000000000000, 400000000000000


class Hail:
    def __init__(self, line):
        self.x, self.y, self.z = map(int, line.split("@")[0].split(","))
        self.dx, self.dy, self.dz = map(int, line.split("@")[1].split(","))

        self.a = self.dy / self.dx
        self.b = self.y - self.a * self.x

    def intersect(self, other):
        if self.a == other.a:
            return False

        x = (other.b - self.b) / (self.a - other.a)
        y = self.a * x + self.b

        if (x - self.x) / self.dx < 0 or (y - other.y) / other.dy < 0:
            return False

        ok = TEST_LO <= x <= TEST_HI and TEST_LO <= y <= TEST_HI
        print(f"({self.x}, {self.y}) -> ({other.x, other.y}) = ({x}, {y}) {ok}")
        return TEST_LO <= x <= TEST_HI and TEST_LO <= y <= TEST_HI


hails = [Hail(line) for line in lines]
print(sum([h1.intersect(h2) for (h1, h2) in itertools.combinations(hails, 2)]))
