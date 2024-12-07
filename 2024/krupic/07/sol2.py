#!/usr/bin/env python3

import sys

def rec(val_acc, exp_acc, exp_tail, res):
    if not exp_tail:
        if val_acc == res:
            return exp_acc
        else:
            return None

    exp_head, exp_tail = exp_tail[0], exp_tail[1:]
    if ops := rec(
        val_acc + exp_head,
        exp_acc + ['+'],
        exp_tail,
        res
    ):
        return ops

    if ops := rec(
        val_acc * exp_head,
        exp_acc + ['*'],
        exp_tail,
        res
    ):
        return ops

    if ops := rec(
        val_acc * 10 ** len(str(exp_head)) + exp_head,
        exp_acc + ['||'],
        exp_tail,
        res
    ):
        return ops


def check(exp, res):
    if ops := rec(exp[0], [], exp[1:], res):
        exp = [exp[0]] + [y for x in zip(ops, exp[1:]) for y in x] + ['=', res]
        print(*exp)
        return True
    else:
        return False

sol = 0
for line in sys.stdin:
    res, exp = line.split(':')
    res = int(res)
    exp = list(map(int, exp.split()))
    if check(exp, res):
        sol += res

print(sol)

