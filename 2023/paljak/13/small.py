input = open("in", "r").read()


def solve_dim(l):
    ret = 0
    for i in range(len(l) - 1):
        ok = True
        for k in range(i + 1):
            if not ok or i + k + 1 == len(l):
                break
            ok &= l[i - k] == l[i + k + 1]
        ret += ok * (i + 1)

    return ret


def solve(note):
    transposed = ["".join(s) for s in zip(*note)]
    return 100 * solve_dim(note) + solve_dim(transposed)


notes = list(map(lambda token: token.split("\n"), input.split("\n\n")))
print(sum([solve(note) for note in notes]))
