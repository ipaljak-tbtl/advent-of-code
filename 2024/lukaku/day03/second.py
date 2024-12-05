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
do = 1

with open(sys.argv[1], 'r') as file:
    for line in file:
        while (ind_mul := line.find("mul(")) != -1:
            ind_do = line.find("do()")
            ind_dont = line.find("don't()")

            if ind_do == -1:
                ind_do = len(line)
            if ind_dont == -1:
                ind_dont = len(line)+1

            if ind_mul < ind_do and ind_mul < ind_dont:
                ind = ind_mul
                line = line[ind+4:]

                ind, num1 = read_num(line)
                if line[ind] != ',':
                    continue
                line = line[ind+1:]

                ind, num2 = read_num(line)
                if line[ind] != ')':
                    continue

                sol += do * num1 * num2
            elif ind_do < ind_dont:
                line = line[ind_do+4:]
                do = 1
            else:
                line = line[ind_dont+7:]
                do = 0

print(sol)
