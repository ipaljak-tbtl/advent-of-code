lines = open("in", "r").readlines()

memo = {}


def dp(i, j, cnt):
    global memo, floor, groups

    if (i, j, cnt) in memo:
        return memo[(i, j, cnt)]
    if i >= len(floor):
        memo[(i, j, cnt)] = j == len(groups)
        return j == len(groups)

    ret = 0
    if floor[i] in ".?" and cnt == 0:
        ret += dp(i + 1, j, 0)

    if floor[i] in "#?" and j < len(groups):
        if cnt + 1 < groups[j]:
            ret += dp(i + 1, j, cnt + 1)
        else:
            if i + 1 == len(floor) or floor[i + 1] in ".?":
                ret += dp(i + 2, j + 1, 0)

    memo[(i, j, cnt)] = ret
    return ret


sol = 0
for line in lines:
    floor = line.split()[0]
    groups = list(map(int, line.split()[1].split(",")))
    memo = {}
    sol += dp(0, 0, 0)

print(sol)
