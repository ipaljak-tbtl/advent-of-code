def solve_section(section, id):
    for line in section.split("\n")[1:]:
        (val, lo, len) = map(int, line.split())
        if lo <= id < lo + len:
            return val + (id - lo)
    return id


def find_location(sections, seed):
    ret = seed
    for section in sections[1:]:
        ret = solve_section(section, ret)
    return ret


input = open("in", "r").read()
sections = input.split("\n\n")
seeds = list(map(int, sections[0].split()[1:]))

print(min([find_location(sections, seed) for seed in seeds]))

ll = [find_location(sections, seed) for seed in seeds]
ss = ll[0]
for i in range(0, len(ll), 2):
    ss = min(ss, ll[i])

print(ss)
