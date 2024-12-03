import re
import sys

REGEX = "mul\((\d|\d\d|\d\d\d),(\d|\d\d|\d\d\d)\)|(do\(\))|(don't\(\))"

input = sys.stdin.read()

total = 0
enabled = True
for x in re.findall(REGEX, input):
    print(x)
    if x[2] == "do()":
        enabled = True
    elif x[3] == "don't()":
        enabled = False
    elif enabled:
        total += int(x[0])*int(x[1])
    
print(total)
