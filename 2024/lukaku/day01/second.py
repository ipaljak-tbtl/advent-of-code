import sys
from collections import Counter

first_list = []
second_list = []

with open(sys.argv[1], 'r') as file:
    for line in file:
        a, b = line.split()
        first_list.append(int(a))
        second_list.append(int(b))

first_list = sorted(first_list)
second_list_counter = Counter(second_list)

print(sum(a * second_list_counter[a] for a in first_list))
