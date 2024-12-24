import sys

reg_a = 0
reg_b = 0
reg_c = 0

with open(sys.argv[1], 'r') as file:
    lines = file.readlines()

    reg_a = int(lines[0][len("Register A: "):])
    reg_b = int(lines[1][len("Register A: "):])
    reg_c = int(lines[2][len("Register A: "):])

    program = list(map(int, lines[4][len("Program: "):].split(',')))
    
inst_pt = 0

print(reg_a, reg_b, reg_c)
print(program)

def combo(operand):
    global reg_a, reg_b, reg_c

    if 0 <= operand and operand <= 3:
        return operand
    if operand == 4:
        return reg_a
    if operand == 5:
        return reg_b
    if operand == 6:
        return reg_c

def adv(operand):
    global reg_a

    reg_a = reg_a // (2 ** combo(operand))

def bxl(operand):
    global reg_b

    reg_b = reg_b ^ operand

def bst(operand):
    global reg_b

    reg_b = combo(operand) % 8

def jnz(operand):
    global inst_pt, reg_a
    if reg_a == 0:
        return

    inst_pt = operand - 2

def bxc(operand):
    global reg_b, reg_c

    reg_b = reg_b ^ reg_c

def out(operand):
    print(combo(operand) % 8, end=',')

def bdv(operand):
    global reg_b, reg_a
    reg_b = reg_a // (2 ** combo(operand))

def cdv(operand):
    global reg_c, reg_a

    reg_c = reg_a // (2 ** combo(operand))

instructions = [adv, bxl, bst, jnz, bxc, out, bdv, cdv]

while True:
    if inst_pt >= len(program):
        break
    opcode = program[inst_pt]

    instruction = instructions[opcode]
    instruction(program[inst_pt+1])
    
    inst_pt += 2
