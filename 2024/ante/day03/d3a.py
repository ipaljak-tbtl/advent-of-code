import re
import sys

REGEX = "mul\((\d|\d\d|\d\d\d),(\d|\d\d|\d\d\d)\)"

input = sys.stdin.read()

total = 0
for x in re.findall(REGEX, input):
    print(x)
    total += int(x[0])*int(x[1])
    
print(total)
