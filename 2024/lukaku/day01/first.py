import sys

first_list = []
second_list = []

with open(sys.argv[1], 'r') as file:
    for line in file:
        a, b = line.split()
        first_list.append(int(a))
        second_list.append(int(b))

first_list = sorted(first_list)
second_list = sorted(second_list)

print(sum(abs(a - b) for a, b in zip(first_list, second_list)))
