import sys
import operator
import itertools
from tqdm import tqdm

def concat(a, b):
    return int(str(a) + str(b))

def possible(test_value, numbers):
    operators = [operator.add, operator.mul, concat]

    for combination in itertools.product(operators, repeat = len(numbers)-1):
        result = numbers[0]
        for i in range(len(numbers)-1):
            result = combination[i](result, numbers[i+1])

        if result == test_value:
            return True

    return False


sol = 0
with open(sys.argv[1], 'r') as file:
    for line in tqdm(file):
        test_value, numbers = line.strip().split(':')

        test_value = int(test_value)
        numbers = list(map(int, numbers.split()))

        if possible(test_value, numbers):
            sol += test_value

print(sol)
