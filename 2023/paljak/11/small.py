lines = open("in", "r").readlines()


def solve_dir(cnt):
    ret, l, r = 0, 0, sum(cnt)
    for i in range(150):
        ret += l * r + (cnt[i] == 0) * l * r
        l += cnt[i]
        r -= cnt[i]
    return ret


r_cnt = [0 for _ in range(150)]
s_cnt = [0 for _ in range(150)]

for i, l in enumerate(lines):
    for j, c in enumerate(l):
        if c == "#":
            r_cnt[i] += 1
            s_cnt[j] += 1

print(solve_dir(r_cnt) + solve_dir(s_cnt))
