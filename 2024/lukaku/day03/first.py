import sys

def read_num(line):
    num = 0

    for i in range(3):
        if line[i].isdigit():
            num = num * 10 + int(line[i])
        else:
            return i, num

    return 3, num

sol = 0

with open(sys.argv[1], 'r') as file:
    for line in file:
        while (ind := line.find("mul(")) != -1:
            line = line[ind+4:]

            ind, num1 = read_num(line)
            if line[ind] != ',':
                continue
            line = line[ind+1:]

            ind, num2 = read_num(line)
            if line[ind] != ')':
                continue

            sol += num1 * num2

print(sol)
