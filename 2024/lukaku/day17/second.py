import sys
from z3 import *

inst_pt = 0
reg_a = 0
reg_b = 0
reg_c = 0

with open(sys.argv[1], 'r') as file:
    lines = file.readlines()

    reg_a = int(lines[0][len("Register A: "):])
    reg_b = int(lines[1][len("Register A: "):])
    reg_c = int(lines[2][len("Register A: "):])

    program = list(map(int, lines[4][len("Program: "):].split(',')))
    
opt = Optimize()

x = BitVec('x', 64)
a, b, c = x, 0, 0

for val in program:
    b = a % 8
    b = b ^ 1
    c = a >> b
    a = a >> 3
    b = b ^ c
    b = b ^ 6
    opt.add((b % 8) == val)
opt.add(a == 0)
opt.minimize(x)

opt.check()
print(opt.model().eval(x))
