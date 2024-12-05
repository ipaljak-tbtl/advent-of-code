import sys

def check_correct(update, rules):
    for i in range(len(update)):
        page = update[i]

        for rule in rules:
            if rule[1] != page:
                continue

            if rule[0] in update:
                ind = update.index(rule[0])

                if ind != -1 and i < ind:
                    return False

    return True

sol = 0

with open(sys.argv[1], 'r') as file:
    rules = []
    for line in file:
        if len(line.strip()) == 0:
            break
        rules.append(list(map(int, line.split('|'))))

    for line in file:
        update = list(map(int, line.split(',')))

        if check_correct(update, rules):
            sol += update[len(update) // 2]

print(sol)

