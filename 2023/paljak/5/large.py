from tqdm import tqdm


def solve_seed(section, id):
    for line in section.split("\n")[1:]:
        (lo, val, len) = map(int, line.split())
        if lo <= id < lo + len:
            return val + (id - lo)
    return id


def find_seed(sections, location):
    ret = location
    for section in sections[1:][::-1]:
        ret = solve_seed(section, ret)
    return ret


input = open("in", "r").read()
sections = input.split("\n\n")
seeds = list(map(int, sections[0].split()[1:]))

upper_bound = 359042615  # obtained from part 1

sol = upper_bound
for location in tqdm(range(upper_bound)):
    seed = find_seed(sections, location)
    ok = False
    for i in range(0, len(seeds), 2):
        ok |= seeds[i] <= seed < seeds[i] + seeds[i + 1]
    if ok:
        sol = location
        break

print(sol)
