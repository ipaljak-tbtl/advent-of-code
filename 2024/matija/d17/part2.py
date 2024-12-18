#!/usr/bin/env python3

def combo(regs, operand):
    return operand if 0 <= operand <= 3 else regs[operand - 4]


regs = [int(input().split()[-1]) for _ in range(3)]
input()
prog = list(map(int, input()[9:].split(',')))
n = len(prog)

adv_denom = None

i = 0
while i < n:
    if prog[i] == 0:
        assert adv_denom is None and 0 <= prog[i+1] <= 3
        adv_denom = 2**prog[i+1]
    i += 2

targets = [0]
for idx in range(n - 1, -1, -1):
    new_targets = []
    for t in targets:
        for a in range(t * adv_denom, (t + 1) * adv_denom):
            regs[0] = a
            ip = 0
            while ip < len(prog):
                opcode, operand = prog[ip:ip+2]
                if opcode == 0:
                    regs[0] //= adv_denom
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
                    if combo(regs, operand) % 8 == prog[idx]:
                        new_targets.append(a)
                    break
                elif opcode == 6:
                    regs[1] = regs[0] // 2**combo(regs, operand)
                elif opcode == 7:
                    regs[2] = regs[0] // 2**combo(regs, operand)

                ip += 2

    targets = new_targets

print(sorted(targets)[0])
