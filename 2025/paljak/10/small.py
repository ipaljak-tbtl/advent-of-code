import itertools

lines = open("in", "r").readlines()

def solve(goal, buttons):
    ret = len(buttons)
    subsets = [list(itertools.combinations(buttons, r)) for r in range(1, len(buttons) + 1)]
    subsets = [list(sublist) for g in subsets for sublist in g]
    for press in subsets:
        curr = [False for _ in range(len(goal))]
        for b in press:
            for x in b:
                curr[x] = not curr[x]
        if curr == goal:
            ret = min(ret, len(press))

    return ret


sol = 0
for line in lines:
    tokens = line.replace("(", "[").replace(")","]").strip().split()
    goal = [x == '#' for x in tokens[0][1:-1]]
    buttons = [eval(str_button) for str_button in tokens[1:-1]]
    sol += solve(goal, buttons)

print(sol)
