input = open("in", "r").read()


def solve_dim(l):
    ret = 0
    for i in range(len(l) - 1):
        diff = 0
        for k in range(i + 1):
            if diff > 1 or i + k + 1 == len(l):
                break
            for ai, bi in zip(l[i - k], l[i + k + 1]):
                diff += ai != bi
        ret += (diff == 1) * (i + 1)

    return ret


def solve(note):
    transposed = ["".join(s) for s in zip(*note)]
    return 100 * solve_dim(note) + solve_dim(transposed)


notes = list(map(lambda token: token.split("\n"), input.split("\n\n")))
print(sum([solve(note) for note in notes]))
