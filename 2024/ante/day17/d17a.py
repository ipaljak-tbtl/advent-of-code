#!/usr/bin/env python3

import sys


class CPU(object):
    def __init__(self, A, B, C, P):
        self.A = A
        self.B = B
        self.C = C
        self.P = P
        self.pc = 0
        self.out = []

    def combo(self, x):
        if x <= 3:
            return x
        elif x == 4:
            return self.A
        elif x == 5:
            return self.B
        elif x == 6:
            return self.C
        else:
            assert False, "Invalid combo operand"

    def adv(self, x):
        divisor = 1 << self.combo(x)
        self.A = self.A // divisor
        self.pc += 2

    def bxl(self, x):
        self.B ^= x
        self.pc += 2

    def bst(self, x):
        self.B = self.combo(x) % 8
        self.pc += 2

    def jnz(self, x):
        if self.A != 0:
            self.pc = x
        else:
            self.pc += 2

    def bxc(self, _):
        self.B ^= self.C
        self.pc += 2

    def out(self, x):
        self.out.append(self.combo(x) % 8)
        self.pc += 2

    def bdv(self, x):
        divisor = 1 << self.combo(x)
        self.B = self.A // divisor
        self.pc += 2

    def cdv(self, x):
        divisor = 1 << self.combo(x)
        self.C = self.A // divisor
        self.pc += 2

    OPS = {
        0: adv,
        1: bxl,
        2: bst,
        3: jnz,
        4: bxc,
        5: out,
        6: bdv,
        7: cdv,
    }

    def debug(self):
        print(f"A: {self.A}, B: {self.B}, C: {self.C}, PC: {self.pc}, OUT: {self.out}")

    def run(self):
        while 0 <= self.pc < len(self.P)-1:
            op = self.P[self.pc]
            arg = self.P[self.pc + 1]
            self.OPS[op](self, arg)
            self.debug()
        return self.out


def main():
    A = int(input().split(":")[1])
    B = int(input().split(":")[1])
    C = int(input().split(":")[1])
    input()
    P = list(map(int, input().split(":")[1].split(",")))
    print(A, B, C, P)
    cpu = CPU(A, B, C, P)
    print(",".join(map(str, cpu.run())))


if __name__ == "__main__":
    main()
