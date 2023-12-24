import z3

lines = open("in", "r").readlines()


class Hail:
    def __init__(self, line):
        self.x, self.y, self.z = map(int, line.split("@")[0].split(","))
        self.dx, self.dy, self.dz = map(int, line.split("@")[1].split(","))


hails = [Hail(line) for line in lines]

solver = z3.Solver()
X, Y, Z, DX, DY, DZ = z3.Reals("X Y Z DX DY DZ")

for i, hail in enumerate(hails):
    ti = z3.Real("t" + str(i))
    solver.add(X + ti * DX == hail.x + ti * hail.dx)
    solver.add(Y + ti * DY == hail.y + ti * hail.dy)
    solver.add(Z + ti * DZ == hail.z + ti * hail.dz)
    solver.add(ti > 0)

solver.check()

print(
    solver.model()[X].as_long()
    + solver.model()[Y].as_long()
    + solver.model()[Z].as_long()
)
