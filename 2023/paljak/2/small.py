lines = open("in", "r").readlines()

RED, GREEN, BLUE = 12, 13, 14


def find_max(color, token):
    if color not in token:
        return 0
    return int(token.split(color)[0].split()[-1])


def solve_line(line):
    game_id = int(line.split(":")[0].split()[1])
    tokens = line.split(":")[1].split(";")

    red = max([find_max("red", token) for token in tokens])
    green = max([find_max("green", token) for token in tokens])
    blue = max([find_max("blue", token) for token in tokens])

    if not (red > RED or green > GREEN or blue > BLUE):
        return game_id

    return 0


print(sum([solve_line(line) for line in lines]))
