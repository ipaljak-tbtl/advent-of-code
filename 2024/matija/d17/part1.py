#!/usr/bin/env python3

def combo(regs, operand):
    return operand if 0 <= operand <= 3 else regs[operand - 4]


regs = [int(input().split()[-1]) for _ in range(3)]
input()
prog = list(map(int, input()[9:].split(',')))

out = []

ip = 0
while ip < len(prog):
    opcode, operand = prog[ip:ip+2]
    if opcode == 0:
        regs[0] //= 2**combo(regs, operand)
    elif opcode == 1:
        regs[1] ^= operand
    elif opcode == 2:
        regs[1] = combo(regs, operand) % 8
    elif opcode == 3 and regs[0]:
        ip = operand
        continue
    elif opcode == 4:
        regs[1] ^= regs[2]
    elif opcode == 5:
        out.append(combo(regs, operand) % 8)
    elif opcode == 6:
        regs[1] = regs[0] // 2**combo(regs, operand)
    elif opcode == 7:
        regs[2] = regs[0] // 2**combo(regs, operand)

    ip += 2

print(','.join(map(str, out)))
