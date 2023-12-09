lines = open("in", "r").readlines()


def solve(l):
    if all(li == 0 for li in l):
        return 0
    return l[-1] + solve([a - b for a, b in zip(l[1:], l)])


sol = 0
for l in lines:
    sol += solve(list(map(int, l.split())))

print(sol)
